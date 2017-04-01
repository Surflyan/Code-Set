// ʵ�ֶ������Ľ����������������Լ�����������
// ���������ֱ�����������������
// ��������������Խ���̵�ȷ��û�а���

#include <iostream>
#include "binary_tree.h"

using namespace std;

//�����������еݹ齨��������
//��������ָ�룬�������飬�±�����
// ���ظ��ڵ�
Node* CreatBinaryTree(Node *&root,char node_array[],int &i)
{
	if (node_array[i] == '#')
		return root;
	
	if (node_array[i] == '$')
	{
		root = NULL;
	}
	else
	{		
		root = new Node;
		root->data = node_array[i];
		CreatBinaryTree(root->lchild, node_array,++i);
		CreatBinaryTree(root->rchild, node_array,++i);     
	}
	return root;
}
void ReleaseBinaryTree(Node *&root)
{
	if (root->left_flag)
		ReleaseBinaryTree(root->lchild);
	if(root->right_flag)
		ReleaseBinaryTree(root->rchild);
	delete root;
	
}

int PreTraverse(Node *&root)
{
	if (root)
	{
		cout << root->data << " ";
		PreTraverse(root->lchild);
		PreTraverse(root->rchild);

	}
	return 0;
}
//����������������
//1.�����������rootΪ�գ��򷵻أ�����
//2 �Խ��root����������
//   2.1  ��rootû�����Һ��ӣ���root���ұ�־��ΪFalse��
//   2.2  �����pre�ұ�־ΪFalse����Ϊpre���Ϻ��������
//   2.3  ��rootû�����ӣ���Ϊroot����ǰ������; 
//   2.4  ��preָ��ոշ��ʵĽ��root�� 
//3 ��root������������������
//4 ��root������������������
Node* pre = NULL;
void PreOrderThreading(Node *&root)
{
	if (root)
	{
		root->left_flag = (root->lchild) ? true : false;
		root->right_flag = (root->rchild) ? true : false;
		if (pre)
		{
			if (pre->right_flag == false)
				pre->rchild = root;
			if (root->left_flag == false)
				root->lchild = pre;
		}
		pre = root;
		if (root->left_flag == true)
			PreOrderThreading(root->lchild);
		if (root->right_flag == true)
			PreOrderThreading(root->rchild);
	}
	return;
}
//����������ĳ���ĺ�̽�����
Node* PreNext(Node *&root)
{
	Node *p;
	p = root;
	if (p->left_flag == true)            //���Ӵ��ڣ����Ӽ�Ϊ���
		return p->lchild;
	else 
		return p->rchild;                //���Ӳ����ڣ��ҽڵ㼴Ϊ���

}
void ShowPreOrderThreading(Node *&root)
{
	Node *p = root;
	do {		
		if (p != NULL)
		{
			cout << p->data << " ";
		}
		p = PreNext(p);
	} while (p != NULL);
	cout << endl;

	return;
	
}

//����������������
Node* g_pre_node = NULL;
void PostOrderThreading(Node *&root)
{
	if (root)
	{
		root->left_flag = (root->lchild) ? true : false;
		root->right_flag = (root->rchild) ? true : false;

		if (root->left_flag)
			PostOrderThreading(root->lchild);
		if (root->right_flag)
			PostOrderThreading(root->rchild);

		if (g_pre_node)
		{
			if (pre->right_flag == false)
				pre->rchild = root;
			if (root->left_flag == false)
				root->lchild = pre;
		}
		pre = root;
	}
	return;
}

// ���Ҷ�����ĳһ���ĸ��ڵ�
//����: ���ڵ㣬��Ÿ��ڵ�ָ�룬���ҵĽ��
void FindParentNode(Node *root,Node *&parent,Node* pnode)
{  
	Node *tnode = root;
	int find_parent = 0;

	if (pnode == root)
	{
	    parent = NULL;
		return ;
	}
	
	if (find_parent == 0)
	{

		if ((tnode->left_flag && tnode->lchild == pnode)
			|| (tnode->right_flag && tnode->rchild == pnode))
		{
			parent = tnode;
			find_parent = 1;
			return ;
		}
		if (find_parent == 0 && tnode->left_flag)
			FindParentNode(tnode->lchild, parent, pnode);
		if (find_parent == 0 && tnode->right_flag)
			FindParentNode(tnode->rchild, parent, pnode);
	}
}
//������������̽ڵ�Ĳ���
//����: ���ڵ㣬�����ҽ��
// 1 ��cur_node�Ǹ�����cur_node�Ǹö���������������������һ�����ʵ��Ľ�㡣cur_node�ĺ�����Ϊ��
// 2 ��cur_node����˫�׵��Һ��ӣ���cur_node�ĺ����̽�������˫�׽��
// 3 ��cur_node����˫�׵����ӣ���cur_node�����ֵܣ�cur_node�ĺ����̽������˫�׽��
// 4 ��cur_node����˫�׵����ӣ���cur_node�����ֵܣ���cur_node�ĺ���������˫�׵���������
//    ��һ������������Ľ�㣬���Ǹ�������"�����µ�Ҷ���"
Node * PostNext(Node *root,Node* cur_node)
{
	
	Node *parent;
	Node *temp_node;
	FindParentNode(root, parent, cur_node);
	if (parent == NULL)
		return NULL;
	if (parent->lchild == cur_node)
	{
		if (parent->right_flag == false)
			return parent;
		else
		{
			temp_node = parent->rchild;
			do
			{
				while (temp_node->left_flag)
					temp_node = temp_node->lchild;
				if (temp_node->right_flag)
					temp_node = temp_node->rchild;
			} while (temp_node->left_flag || temp_node->right_flag);
			return temp_node;
		}
	}
	else
		return parent;
}
void ShowPostOrderThreading(Node *& root)
{
	Node *p = root;
	while (p->left_flag)
		p = p->lchild;
	cout << p->data << " ";
	do {
		p = PostNext(root,p);
		if (p != NULL)
		{
			cout << p->data << " ";
		}
		
	} while (p != NULL);
	cout << endl;

	return;
}
int main()
{
	char node_array[] = { "FBA$$DC$$E$$G$IH$$$#" };
	Node *T1,*T2;
	int i = 0;
	CreatBinaryTree(T1, node_array,i);
	
	cout << "�����������������У�" << endl;
	PreOrderThreading(T1);
	ShowPreOrderThreading(T1);
	ReleaseBinaryTree(T1);

	i = 0;
	CreatBinaryTree(T2, node_array, i);
	cout << "�����������������У�" << endl;
	PostOrderThreading(T2);
	ShowPostOrderThreading(T2);
	ReleaseBinaryTree(T2);
}
