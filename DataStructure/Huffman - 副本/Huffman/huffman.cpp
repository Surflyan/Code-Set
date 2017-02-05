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
//��ȡ�ļ������ַ����ַ�����Ƶ�ʴ��ڶ�Ӧ�ַ���㣨HuffmanTree[i])��
void ReadText(char fileName[])
{
	FILE *fp;
	if ((fp = fopen(fileName, "rb")) == NULL)
	{
		printf("the file can not be open!");
		exit(0);
	}

	 for (int i = 0; i < 512; i++)           //  ��ʼ���ַ����
	{
	    HuffmanTree[i].c = (unsigned char)i;
		HuffmanTree[i].weight = 0;
		HuffmanTree[i].lchild = -1;
		HuffmanTree[i].rchild = -1;
		HuffmanTree[i].parent = -1;
	}

	unsigned char cha;
	while (fread(&cha, 1, 1, fp))
	{
		HuffmanTree[cha].weight++;      //����Ƶ�ʣ�
		fileLength++;

	}
	fclose(fp);
}

int SortFileChar()
{   
	int i,j;
	charNode temp;
	for (i = 0; i < 256; i++)                   //��Ƶ������
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
	int index;                      //��¼��Сֵ�±�
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
void CreatHuffmanTree()
{
	int i = 0;
	int numNode;
	int lChildIndex, rChildIndex;
	SortFileChar();
	fileCharKind = FindFileChaNumber();              //�ַ���
	numNode = fileCharKind*2 - 1  ;                 //�ڵ���

	for (i = fileCharKind; i < numNode; i++)            //����
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

void HuffmanCode()
{
	int i,j,k;
	int codelen;
	for (i = 0; i < fileCharKind; i++)
	{   
		j = i;
		while (HuffmanTree[j].parent != -1)
		{
			k = j;
			j= HuffmanTree[j].parent;

			if (HuffmanTree[j].lchild == k)
			{
				codelen = strlen(HuffmanTree[i].hufCode);
				memmove(HuffmanTree[i].hufCode + 1, HuffmanTree[i].hufCode, codelen);
				HuffmanTree[i].hufCode[0] = '0';
			}
			else
			{
				codelen = strlen(HuffmanTree[i].hufCode);
				memmove(HuffmanTree[i].hufCode + 1, HuffmanTree[i].hufCode, codelen);
				HuffmanTree[i].hufCode[0] = '1';
			}
		}
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
	fprintf(fp, "����������\n");
	int i;

	for (i = 0; i < fileCharKind; i++)
	{
		if (HuffmanTree[i].weight != 0)
			fprintf(fp, "%c  %s\n", HuffmanTree[i].c, HuffmanTree[i].hufCode);
	}
	printf("Creat Successfully��\n");
	fclose(fp);
	return 0;
}

/*����ѹ���ļ���ѹ���ļ�д���Ĳ���
 1.�ļ���ʶ   2.�ļ��ַ������� 3.�ļ��ַ������� 4.�ַ������� 5.�ļ�����*/
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
	//�ļ�ͷ��д��
	int signal=1997;                   //�����ѹ���ļ���ʶ
	fseek(ofp, 0, SEEK_SET);
	fwrite(&signal, sizeof(int), 1, ofp);

	fseek(ofp, 4, SEEK_SET);
	fwrite(&fileLength, sizeof(long), 1, ofp);

	fseek(ofp, 8, SEEK_SET);
	fwrite(&fileCharKind, sizeof(int), 1, ofp);

	fseek(ofp, 12, SEEK_SET);                         //д���ַ������Ϣ
	for (int i = 0; i <2*fileCharKind-1; i++)
	{
		fwrite(&HuffmanTree[i], sizeof(charNode), 1, ofp);
	}
	//д��ѹ���ļ�����


	char buf[N]; buf[0] = 0;             //��ֹ���������
	unsigned char c;
	int i;
	int bufLen;
	long localFileLength = 0;
	while ((fread(&c, 1, 1, ifp)))
	{
		for (i = 0; i < fileCharKind; i++)
		{
			if (c == HuffmanTree[i].c)
				break;
		}
		strcat(buf, HuffmanTree[i].hufCode);
		bufLen = strlen(buf);
		c = 0;

		while (bufLen >= 8)
		{
			for (i = 0; i < 8; i++)
			{
				if (buf[i] == '1')                        //������λ
					c = (c << 1) | 1;
				else
					c = c << 1;
			}
			fwrite(&c, 1, 1, ofp);
			strcpy(buf, buf + 8);
			bufLen = strlen(buf);
		}
		if (localFileLength == fileLength)
			break;
	}

	if (bufLen > 0)                       //���һ�ַ��Ĵ���
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
		printf("���ļ��ǲ��ù�����ѹ����\n	");
		exit(0);
	}

	fread(&localFileLen, sizeof(long), 1, ifp);
	fread(&localCharKind, sizeof(int), 1, ifp);
	
	for (int i = 0; i < 2*localCharKind-1; i++)
	{
		fread(&reHuffmanTree[i], sizeof(charNode), 1, ifp);
	}


	 //��huffmanTree ���ڵ�
	for ( int i = 0; i < 2 * localCharKind - 1; i++)
	{
		if (reHuffmanTree[i].parent == -1)
		{   
			rootIndex = i;
			break;
		}
	}


	unsigned char c;
	long cNum;
	char buf[N]; 
	char charBuf[N]; charBuf[0] = 0;
	int buflen;
	int hufCodeMaxLen;
	long writeCharNumber = 0;
	hufCodeMaxLen = strlen(reHuffmanTree[localCharKind - 1].hufCode);
	while (1)
	{   
		writeCharNumber++;
		while (strlen(charBuf)<hufCodeMaxLen)
		{
			fread(&c, sizeof(unsigned char), 1, ifp);
			cNum = c;
			itoa(cNum, buf, 2);
			buflen = strlen(buf);
			for (int i = 8; i > buflen; i--)
			{
				strcat(charBuf, "0");
			}
			strcat(charBuf, buf);
		}
		int i=rootIndex;
		int j = 0;
		while (reHuffmanTree[i].rchild!=-1||reHuffmanTree[i].lchild!=-1)
		{
			if (charBuf[j] == '0')
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
		strcpy(charBuf, charBuf + strlen(reHuffmanTree[i].hufCode));
		if (writeCharNumber == localFileLen)
			break;
	}
	fclose(ifp);
	fclose(ofp);

}

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
	fseek(OFP, 0, SEEK_END);
	orignalFileLen=ftell(OFP);

	fseek(CFP, 0, SEEK_END);
	compressFileLen = ftell(CFP);

	compressRate = float(compressFileLen) / orignalFileLen;
	return compressRate;
	fclose(OFP);
	fclose(CFP);

}