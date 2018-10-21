#ifndef HUFFMAN_H
#define HUFFMAN_H
#define N 50
struct charNode
{
	unsigned char c;               //文件字符
	long weight;                     //字符频率
	int parent, lchild, rchild;     //huffman树
	char  hufCode[N];                //huffman编码
	int   hufCodeLen;                //huf编码长度
};

extern charNode  HuffmanTree[512];

extern void ReadText(char fileName[]);               //读取文件
extern int FindMinWeightChar(int preMinIndex);       //找到最小权值元素
extern int FindFileChaNumber();                     //文件字符种类
extern void CreatHuffmanTree();                     //建树
extern void HuffmanCode();                          //编码
extern int WritePassToFile(char passFileName[]);     //写编码
extern int CompressFile(char FileName[],char CompreFileName[]);            //压缩
extern int DecompressFile(char compressFileName[],char decompressFileName[]); //解压
extern float CalcCompressibility(char fileName[], char compressFileName[]);       //计算压缩率
#endif 
