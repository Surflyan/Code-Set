#include <iostream>
#include <string.h>
#include <cstdio>
#include "huffman.h"

using namespace std;

long fileLength = 0;
int fileCharKind = 0;
charNode  HuffmanTree[512];

void ReadText(char fileName[]);
int FindMinWeightChar(int preMinIndex);
int FindFileChaNumber();
void CreatHuffmanTree();
void HuffmanCode();
int WritePassToFile(char passFileName[]);
int CompressFile(char FileName[],char CompressFile[]);
int DecompressFile(char compressFileName[],char decompressFileName[]);
float CalcCompressibility(char fileName[], char compressFileName[]);
//读取文件，将字符及字符出现频率存在对应字符结点（HuffmanTree[i])中
void ReadText(char fileName[])
{
	FILE *fp;
	if ((fp = fopen(fileName, "rb")) == NULL)
	{
		printf("the file can not be open!");
		exit(0);
	}

	 for (int i = 0; i < 512; i++)           //  初始化字符结点
	{
	    HuffmanTree[i].c = (unsigned char)i;
		HuffmanTree[i].weight = 0;
		HuffmanTree[i].lchild = -1;
		HuffmanTree[i].rchild = -1;
		HuffmanTree[i].parent = -1;
		HuffmanTree[i].hufCodeLen = 0;
	}

	unsigned char cha;
	while (fread(&cha, 1, 1, fp))
	{
		HuffmanTree[cha].weight++;      //计算频率；
		fileLength++;

	}
	fclose(fp);
}

//将字符数组按字符权重排序，大到小
int SortFileChar()
{   
	int i,j;
	charNode temp;
	for (i = 0; i < 256; i++)                   //按频率排序；
	{
		for (j = i + 1; j < 256; j++)
		{
			if (HuffmanTree[i].weight < HuffmanTree[j].weight)
			{
				temp = HuffmanTree[i];
				HuffmanTree[i] = HuffmanTree[j];
				HuffmanTree[j] = temp;
			}
		}
	}
	return 0;
}

int FindMinWeightChar(int preMinIndex)
{
	int i;
	int index;                      //纪录最小值下标
	long min =2147483647;          
	for (i = 0; i < preMinIndex; i++)
	{
		if (HuffmanTree[i].weight == 0 || HuffmanTree[i].parent != -1)
			continue;
		if (HuffmanTree[i].weight < min)
		{
			min = HuffmanTree[i].weight;
			index = i;
		}

	}
	return index;
}

int FindFileChaNumber()
{
	int i = 0;
	while (i <256)
	{
		if (HuffmanTree[i].weight == 0)
			break;
		i++;
	}
	return i;
}

//建立哈夫曼树，通过字符数组下标来建树
void CreatHuffmanTree()
{
	int i = 0;
	int numNode;
	int lChildIndex, rChildIndex;
	SortFileChar();
	fileCharKind = FindFileChaNumber();              //字符数
	numNode = fileCharKind*2 - 1  ;                 //节点数

	for (i = fileCharKind; i < numNode; i++)            //建树
	{
		lChildIndex = FindMinWeightChar(i);
		HuffmanTree[i].lchild = lChildIndex;
		HuffmanTree[lChildIndex].parent = i;

		rChildIndex = FindMinWeightChar(i);
		HuffmanTree[i].rchild = rChildIndex;
		HuffmanTree[rChildIndex].parent = i;

		HuffmanTree[i].weight = HuffmanTree[lChildIndex].weight + HuffmanTree[rChildIndex].weight;

	}
}

//生成每个字符对应哈夫曼编码，自上而下
void HuffmanCode()
{
	int i,j,k;
	for (i = 0; i < fileCharKind; i++)
	{   
		j = i;
		int hufCodeIndex = 0;
		while (HuffmanTree[j].parent != -1)
		{  
			k = j;
			j= HuffmanTree[j].parent;
			if (HuffmanTree[j].lchild == k)
			{
				HuffmanTree[i].hufCode[hufCodeIndex++] = '0';
			}
			else
			{
				HuffmanTree[i].hufCode[hufCodeIndex++] = '1';
			}
		}


		//将生成的huf编码倒置
		int t = 0;
		hufCodeIndex--;
		while (t < hufCodeIndex)
		{
			int temp;
			temp = HuffmanTree[i].hufCode[t];
			HuffmanTree[i].hufCode[t] = HuffmanTree[i].hufCode[hufCodeIndex];
			HuffmanTree[i].hufCode[hufCodeIndex] = temp;
			t++;
			hufCodeIndex--;
		}
		HuffmanTree[i].hufCodeLen = strlen(HuffmanTree[i].hufCode);
	}

}

int WritePassToFile(char passFileName[])
{
	FILE *fp;
    
	fp = fopen(passFileName, "w");

	if (fp == NULL)
	{
		printf("The file can not be open!\n");
		return 0;
	}
	fprintf(fp, "哈夫曼编码\n");
	int i;

	for (i = 0; i < fileCharKind; i++)
	{
		if (HuffmanTree[i].weight != 0)
			fprintf(fp, "%c  %s\n", HuffmanTree[i].c, HuffmanTree[i].hufCode);
	}
	printf("Creat Successfully！\n");
	fclose(fp);
	return 0;
}

/*创建压缩文件，压缩文件写入四部分
 1.文件标识   2.文件字符个数， 3.文件字符种类数 4.字符结点编码 5.文件内容*/
int CompressFile(char FileName[],char CompressFileName[])
{
	FILE *ofp;
	if ((ofp = fopen(CompressFileName,"wb"))==NULL)
	{
		printf("Creat Huffman code book failed!");
		exit(0);
	}

	FILE *ifp;
	if ((ifp = fopen(FileName, "rb")) == NULL)
	{
		printf("Open %s file failed!\n",FileName);
		exit(0);
	}
	//文件头的写入
	int signal=1997;                   //此软件压缩文件标识
	fseek(ofp, 0, SEEK_SET);
	fwrite(&signal, sizeof(int), 1, ofp);

	fseek(ofp, 4, SEEK_SET);
	fwrite(&fileLength, sizeof(long), 1, ofp);

	fseek(ofp, 8, SEEK_SET);
	fwrite(&fileCharKind, sizeof(int), 1, ofp);

	fseek(ofp, 12, SEEK_SET);                         //写入字符结点信息
	for (int i = 0; i <2*fileCharKind-1; i++)
	{
		fwrite(&HuffmanTree[i], sizeof(charNode), 1, ofp);
	}
	//写入压缩文件内容


	char buf[N]; buf[0] = 0;             //防止缓存器溢出
	unsigned char c;
	int i;
	int bufLen=0;
	long localFileLength = 0;
	while ((fread(&c, 1, 1, ifp)))
	{
		for (i = 0; i < fileCharKind; i++)
		{
			if (c == HuffmanTree[i].c)
				break;
		}
		strcat(buf, HuffmanTree[i].hufCode);
		bufLen += HuffmanTree[i].hufCodeLen;
		c = 0;

		while (bufLen >= 8)
		{
			for (i = 0; i < 8; i++)
			{
				if (buf[i] == '1')                        //编码移位
					c = (c << 1) | 1;
				else
					c = c << 1;
			}
			fwrite(&c, 1, 1, ofp);
			strcpy(buf, buf + 8);
			bufLen = bufLen-8;
		}
		if (localFileLength == fileLength)
			break;
	}

	if (bufLen > 0)                       //最后一字符的处理
	{
		strcat(buf, "00000000");
		for (i = 0; i < 8; i++)
		{
			if (buf[i] == '1')
				c = (c << 1) | 1;
			else
				c = c << 1;
		}
		fwrite(&c, 1, 1, ofp);
		strcpy(buf, buf + 8);
	}
	fclose(ofp);
	fclose(ifp);
	return 0;
}

void CharToBinary(char c, char buf[])
{   
	int i;
	for ( i = 0; i < 8; i++)
	{
		buf[i]=(c>>(7-i)&1)+'0';
	}
}
int DecompressFile(char compressFileName[], char decompressFileName[])
{
	FILE *ofp;
	if ((ofp = fopen(decompressFileName, "wb")) == NULL)
	{
		printf("Creat Decompress File failed!\n");
		exit(0);
	}

	FILE *ifp;
	if ((ifp = fopen(compressFileName, "rb")) == NULL)
	{
		printf("Open %s failed!\n",compressFileName);
		exit(0);
	}

	int signal;
	int localFileLen;
	int localCharKind;
	charNode reHuffmanTree[512];
	int rootIndex;

	fread(&signal, sizeof(int), 1, ifp);
	if (signal != 1997)
	{
		printf("此文件非采用哈夫曼压缩！\n	");
		exit(0);
	}

	fread(&localFileLen, sizeof(long), 1, ifp);
	fread(&localCharKind, sizeof(int), 1, ifp);
	
	for (int i = 0; i < 2*localCharKind-1; i++)
	{
		fread(&reHuffmanTree[i], sizeof(charNode), 1, ifp);
	}


	 //找huffmanTree 根节点
	for ( int i = 0; i < 2 * localCharKind - 1; i++)
	{
		if (reHuffmanTree[i].parent == -1)
		{   
			rootIndex = i;
			break;
		}
	}

	//将编码对应字符写入解码文件
	unsigned char c;
	char buf[N]; 
	char charBuf[N]; charBuf[0] = 0;
	int hufCodeMaxLen;
	int charBufLen = 0;
	long writeCharNumber = 0;
	hufCodeMaxLen = strlen(reHuffmanTree[localCharKind - 1].hufCode);
	while (1)
	{   
		writeCharNumber++;
		while (charBufLen<hufCodeMaxLen)
		{
			fread(&c, sizeof(unsigned char), 1, ifp);
			CharToBinary(c, buf);
			int i = 0;
			while ( i < 8)
			{
				charBuf[charBufLen++] = buf[i++];
			}

		}
		int i=rootIndex;
		int j = 0;
		while (reHuffmanTree[i].rchild!=-1||reHuffmanTree[i].lchild!=-1)
		{
			if (charBuf[j] =='0')
			{
				i = reHuffmanTree[i].lchild;
			}
			else
			{
				i = reHuffmanTree[i].rchild;
			}
			j++;
		}
		c = reHuffmanTree[i].c;
		fwrite(&c, 1, 1,ofp);
		int t= 0;
		charBufLen -= reHuffmanTree[i].hufCodeLen;
		while (t < charBufLen)
		{
			charBuf[t] = charBuf[t + reHuffmanTree[i].hufCodeLen];
		    t++;
		}
		if (writeCharNumber == localFileLen)
			break;
	}
	fclose(ifp);
	fclose(ofp);

	return 0;

}

//计算压缩率
float CalcCompressibility(char fileName[], char compressFileName[])
{
	FILE *OFP, *CFP;
	if ((OFP = fopen(fileName, "rb")) == NULL)
	{
		printf("the file %s can not be open!\n", fileName);
		exit(0);
	}

	if ((CFP = fopen(compressFileName, "rb")) == NULL)
	{
		printf("the file %s can not be open!\n", compressFileName);
		exit(0);
	}

	long orignalFileLen;
	long compressFileLen;
	float compressRate;
	fseek(OFP, 0, SEEK_END);                    //计算文件大小
	orignalFileLen=ftell(OFP);           

	fseek(CFP, 0, SEEK_END);
	compressFileLen = ftell(CFP);

	compressRate = float(compressFileLen) / orignalFileLen;
	return compressRate;
	fclose(OFP);
	fclose(CFP);

}