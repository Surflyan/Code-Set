#ifndef HUFFMAN_H
#define HUFFMAN_H
#define N 50
struct charNode
{
	unsigned char c;               //�ļ��ַ�
	long weight;                     //�ַ�Ƶ��
	int parent, lchild, rchild;     //huffman��
	char  hufCode[N];                //huffman����
	int   hufCodeLen;                //huf���볤��
};

extern charNode  HuffmanTree[512];

extern void ReadText(char fileName[]);               //��ȡ�ļ�
extern int FindMinWeightChar(int preMinIndex);       //�ҵ���СȨֵԪ��
extern int FindFileChaNumber();                     //�ļ��ַ�����
extern void CreatHuffmanTree();                     //����
extern void HuffmanCode();                          //����
extern int WritePassToFile(char passFileName[]);     //д����
extern int CompressFile(char FileName[],char CompreFileName[]);            //ѹ��
extern int DecompressFile(char compressFileName[],char decompressFileName[]); //��ѹ
extern float CalcCompressibility(char fileName[], char compressFileName[]);       //����ѹ����
#endif 
