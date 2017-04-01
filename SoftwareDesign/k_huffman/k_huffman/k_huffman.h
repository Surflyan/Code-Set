#ifndef K_HUFFMAN_H
#define K_HUFFMAN_H
#define MaxNum 128
#define MaxCodeLen 10

#define K 5              //K叉huffman tree
int g_num_leaf_node;      //字符数


struct HufNode
{   
	char cha;
	int weight;
	HufNode *child;              //指向第一个孩子
	HufNode *sibling;            //若是最后一个孩子，指向parent，否则指向右sibling
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
