#include <iostream>
#include <stdio.h>
#include "k_huffman.h"

using namespace std;
//��ȡ�ļ������ַ����ַ�����Ƶ�ʴ��ڶ�Ӧ�ַ�������weight�����У���asciiֵΪ�±�
void ReadText(int weight[])
{
	FILE *fp;
	if ((fp = fopen("cha.txt", "rb")) == NULL)
	{
		printf("the file can not be open!");
		exit(0);
	}

	for (int i = 0; i < MaxNum; i++)           //  ��ʼ���ַ����
	{
		weight[i] = 0;
	}

	unsigned char c;
	while (fread(&c, 1, 1, fp))
	{
		weight[c]++;                           //����Ƶ�ʣ�

	}
	fclose(fp);
}

//����weight���齨�������������Ȩֵ��С����
//����InsertHufNode����ʵ��
// ����g_num_leaf_node ,��Ҫ������ַ���
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

//����Ȩֵ��С��������㣬��HufNode sibling����
//������headָ�룬�ַ���Ȩֵ
//���أ����ɵĽ��
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

//LeafNode �ṹ�洢Ҷ�ӽ��ָ�룬��ֹBuildHufTree �󣬶�ʧҶ�ӽ�㡣
//LeafNode �е�lnode�洢Ҷ�ӽ��ָ�룬code �洢����
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
// �ͷ�Ҷ�ӽ��,���ִ��
int ReleaseLeafNode(LeafNode*leaf)
{
	delete[]leaf;
	return 0;
}

//����K0=(n-1)%(k-1),���ȨֵΪ0�Ľ��
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

// ����Huffman���� ����ͷ�ڵ���head->sibling
//ȡ�����е�ǰk�����������������һ���µĽ�����丸��㣬������ȨֵΪ��k������������Ȩֵ֮�ͣ�
//�ڲ���������Ϊ������tag ֵ������K-1��K-2...0 
//���²����ĸ���㰴������������С�
// child ָ��ý��ĵ�һ������
// sibling ����tag=0ʱ��ָ��ý��ĸ���㣬�Ҹý��Ϊ�丸�������һ�����Ӽ���k�����ӣ� 
//            ��tag = n ʱ��ָ��ý�����һ���ֵܣ��Ҹý��Ϊ�丸���ĵ�k - n�����ӡ�
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

//������ HufTree��head��Ҷ�ӽ������
// ����Ҷ�ӽ�㣬���¶��ϣ��ҵ�ÿ��parent ��㣬ÿ������tagֵ��Ϊ���룬
// ��ÿ���ַ��ı��� �������� leaf.code �У������һλ��ű����λ�������㵹�����
int BuildCoding(HufNode *head, LeafNode *leaf)
{
	int i = 0;
	int j = 1;
	while (i < g_num_leaf_node)
	{   
		HufNode *hnode = leaf[i].lnode;
		j = 1;
		while (hnode != head->sibling)    //����HufTreeRoot
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

//�������ֵ�������鵹��
int OutPutCoding(LeafNode*leaf)
{
	int i = 0;
	cout << "�������£�" << endl;
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

//������ leaf���ַ�
// �����ҵ��ַ����������
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
		cout << "û���ַ�" << cha << "�ı���" << endl;
	return 0;
}

//������head, �������飬���볤��
//���϶��£����ձ���ֵ���ҵ���  K-code ������ ,ֱ������Ҷ��
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
		cout <<endl<< "		1. �������" << endl;
		cout << "		2. ����" << endl;
		cout << "		3. ����" << endl;
		cout << "		   �����˳�" << endl;
		cout << "		��ѡ��" << endl;
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
			cout << "�����ַ�:" << endl;
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
			//����
			getchar();
			cout << "������룺" << endl;
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