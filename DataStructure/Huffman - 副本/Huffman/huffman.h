#ifndef HUFFMAN_H
#define HUFFMAN_H
#define N 50
struct charNode
{
	unsigned char c;               //�ļ��ַ�
	long weight;                     //�ַ�Ƶ��
	int parent, lchild, rchild;     //huffman��
	char  hufCode[N];                //huffman����
};

extern charNode  HuffmanTree[512];

extern void ReadText(char fileName[]);
extern int FindMinWeightChar(int preMinIndex);
extern int FindFileChaNumber();
extern void CreatHuffmanTree();
extern void HuffmanCode();
extern int WritePassToFile(char passFileName[]);
extern int CompressFile(char FileName[],char CompreFileName[]);
extern int DecompressFile(char compressFileName[],char decompressFileName[]);
extern float CalcCompressibility(char fileName[], char compressFileName[]);
#endif 
