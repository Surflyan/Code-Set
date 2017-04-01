#include <iostream>
#include <stdio.h>
#include "k_huffman.h"

using namespace std;
//读取文件，将字符及字符出现频率存在对应字符结点存在weight数组中，以ascii值为下标
void ReadText(int weight[])
{
	FILE *fp;
	if ((fp = fopen("cha.txt", "rb")) == NULL)
	{
		printf("the file can not be open!");
		exit(0);
	}

	for (int i = 0; i < MaxNum; i++)           //  初始化字符结点
	{
		weight[i] = 0;
	}

	unsigned char c;
	while (fread(&c, 1, 1, fp))
	{
		weight[c]++;                           //计算频率；

	}
	fclose(fp);
}

//根据weight数组建立结点链表，按照权值大小链接
//调用InsertHufNode函数实现
// 返回g_num_leaf_node ,即要编码的字符数
int SetHufNodeLink(HufNode*head,int weight[])
{
	int i = 0;
	g_num_leaf_node = 0;
	while (i < MaxNum)
	{   
		if (weight[i] != 0)
		{
			InsertHufNode(head, unsigned char(i), weight[i]);
			g_num_leaf_node++;
		}
		i++;
	}
	return g_num_leaf_node;
}

//按照权值由小到大插入结点，以HufNode sibling链接
//参数：head指针，字符，权值
//返回：生成的结点
HufNode * InsertHufNode(HufNode *head, unsigned char c, int weight)
{
	HufNode *pre_node, *current_node;

	current_node = head->sibling;
	pre_node = head;
	while (current_node != NULL && current_node->weight < weight)
	{
		current_node = current_node->sibling;
		pre_node = pre_node->sibling;
	}
	HufNode *new_node = new HufNode;
	new_node->cha = c;
	new_node->weight = weight;
	new_node->child = NULL;
	new_node->sibling = pre_node->sibling;

	pre_node->sibling = new_node;

	return new_node;

}

//LeafNode 结构存储叶子结点指针，防止BuildHufTree 后，丢失叶子结点。
//LeafNode 中的lnode存储叶子结点指针，code 存储编码
LeafNode* BuildLeafLink(HufNode*head)
{
	LeafNode*leaf = new LeafNode[g_num_leaf_node];
	HufNode *hnode = head->sibling;
	int node_index = 0;
	while (hnode != NULL)
	{   
		leaf[node_index++].lnode = hnode;
		hnode = hnode->sibling;
	}
	return leaf;
}
// 释放叶子结点,最后执行
int ReleaseLeafNode(LeafNode*leaf)
{
	delete[]leaf;
	return 0;
}

//根据K0=(n-1)%(k-1),添加权值为0的结点
int AddHufNode(HufNode *head)
{
	int k0 = (g_num_leaf_node - 1) % (K - 1);
	if (k0 == 0)
		return 0;
	int i = K - 1 - k0;
	while (i > 0)
	{
		InsertHufNode(head, unsigned char(0), 0);
		i--;
	}
	return 0;
}

// 建立Huffman树， 该树头节点在head->sibling
//取链表中的前k个结点作子树，产生一个新的结点作其父结点，父结点的权值为这k棵子树根结点的权值之和；
//在产生过程中为结点添加tag 值，按照K-1，K-2...0 
//将新产生的父结点按升序插入链表中。
// child 指向该结点的第一个孩子
// sibling ：当tag=0时，指向该结点的父结点，且该结点为其父结点的最后一个孩子即第k个孩子； 
//            当tag = n 时，指向该结点的下一个兄弟，且该结点为其父结点的第k - n个孩子。
int BuildHufTree(HufNode *head)
{
	HufNode *hnode = head->sibling;	
	int j = 0;
	HufNode *last_sibling;
	HufNode *first_child;
	while (hnode != NULL)
	{   
	
		int num = K;
		int weight = 0;
		
		first_child = hnode;
		while (num > 0 && hnode!=NULL)
		{
			weight += hnode->weight;
			hnode->tag = num - 1;
			if (hnode->tag==0)
				last_sibling = hnode;
			hnode = hnode->sibling;
			num--;
			
		}
		
		last_sibling->sibling = InsertHufNode(head, unsigned char(0), weight);
		last_sibling->sibling->child = first_child;
	}
	head->sibling = last_sibling->sibling;
	return 0;
}

//参数： HufTree：head，叶子结点链表
// 按照叶子结点，自下而上，找到每个parent 结点，每个结点的tag值即为编码，
// 将每个字符的编码 倒序存放在 leaf.code 中，数组第一位存放编码的位数，方便倒叙输出
int BuildCoding(HufNode *head, LeafNode *leaf)
{
	int i = 0;
	int j = 1;
	while (i < g_num_leaf_node)
	{   
		HufNode *hnode = leaf[i].lnode;
		j = 1;
		while (hnode != head->sibling)    //到达HufTreeRoot
		{  
			leaf[i].code[j++] = hnode->tag;
			while (hnode->tag != 0)
			{
				hnode = hnode->sibling;
			}
			hnode = hnode->sibling;
		}
		leaf[i].code[0] = j-1;
		i++;
	}
	return 0;
}

//输出编码值，按数组倒叙
int OutPutCoding(LeafNode*leaf)
{
	int i = 0;
	cout << "编码如下：" << endl;
	while (i < g_num_leaf_node)
	{
		int j = leaf[i].code[0];
		cout << leaf[i].lnode->cha << " : ";
		while (j > 0)
		{
			cout << leaf[i].code[j--];
		}
		cout << endl;
		i++;
	}
	return 0;
}

//参数： leaf，字符
// 遍历找到字符，输出编码
int Coding(LeafNode *leaf,char cha)
{
	int i = 0;
	while (i < g_num_leaf_node)
	{
		if (leaf[i].lnode->cha == cha)
		{
			int j = leaf[i].code[0];
		 	while (j > 0)
			{cout << leaf[i].code[j--];	}
			break;
		}
		i++;
	}
	if (i == g_num_leaf_node)
		cout << "没有字符" << cha << "的编码" << endl;
	return 0;
}

//参数：head, 编码数组，编码长度
//自上而下，按照编码值，找到第  K-code 个孩子 ,直到到达叶子
int Decoding(HufNode *head, int code[],int codelen)
{
	
	int i = 0;
	while (i < codelen)
	{  
		HufNode *hnode = head->sibling;
		while (hnode->child != NULL)
		{
			int j = code[i++];
			hnode = hnode->child;
			int t = K - 1 - j;
			while (t> 0)
			{
				hnode = hnode->sibling;
				t--;
			}
			
		}

		cout << hnode->cha;

	}
	cout << endl;
	return 0;
}


int Release(HufNode *head)
{  
	if (head)
	{
		Release(head->child);
		if (head->tag ==0)
		{		return 0;
		}
		Release(head->sibling);
		delete head;
	}
	return 0;
}

int main()
{
	int Weight[MaxNum];
	ReadText(Weight);

	HufNode *head = new HufNode;
	head->weight = 0;
	head->child = NULL;
	head->sibling = NULL;

	SetHufNodeLink(head, Weight);
	LeafNode *leaf;
	leaf=BuildLeafLink(head);
	AddHufNode(head);
	BuildHufTree(head);
	BuildCoding(head,leaf);

	char op;
	while (true)
	{   
		cout <<endl<< "		1. 输出编码" << endl;
		cout << "		2. 编码" << endl;
		cout << "		3. 解码" << endl;
		cout << "		   其他退出" << endl;
		cout << "		请选择：" << endl;
		cin >> op;
		switch (op)
		{
		case('1'):
		{
			OutPutCoding(leaf);
			break;
		}
		case('2'):
		{
			//coding
			getchar();
			cout << "输入字符:" << endl;
			while (cin.get() != '\n')
			{
				char ch;
				cin.unget();
				cin >> ch;
				Coding(leaf, ch);
			}
			break;
		}
		case('3'):
		{
			//解码
			getchar();
			cout << "输入编码：" << endl;
			int i = 0;
			int code[MaxNum];
			while (cin.get() != '\n')
			{
				char x;
				cin.unget();
				cin >> x;
				code[i++] = x - 48;
			}
			Decoding(head, code, i);
			break;
		}
		default:
		{
			Release(head->sibling);
			ReleaseLeafNode(leaf);
			exit(0);
		}
		}
	}
	
    return 0;
    
}