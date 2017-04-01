#ifndef K_HUFFMAN_H
#define K_HUFFMAN_H
#define MaxNum 128
#define MaxCodeLen 10

#define K 5              //K��huffman tree
int g_num_leaf_node;      //�ַ���


struct HufNode
{   
	char cha;
	int weight;
	HufNode *child;              //ָ���һ������
	HufNode *sibling;            //�������һ�����ӣ�ָ��parent������ָ����sibling
	int tag;
};

struct LeafNode
{
	HufNode* lnode;
	int code[MaxCodeLen] = { -1 };
};

void ReadText(int weight[]);
int SetHufNodeLink(HufNode*head, int weight[]);
HufNode* InsertHufNode(HufNode *head, unsigned char c, int weight);




#endif
