#include<stdio.h>
#ifndef BI_TREE_H
#define BI_TREE_H

struct BiTreeNode              
{
	char e;                   //������
	BiTreeNode* lchild;       //����
	BiTreeNode* rchild;       //�Һ���

};

struct BiTreeNodeFlag          //���������Ҫ�����ӷ��ʱ�־
{
	BiTreeNode *Node; 
	int Flag = 0;
};


//���������࣬����������ز���
class BinaryTree
{
public :
	BinaryTree() { root=NULL; }
	~BinaryTree() { Release(root); }                //�����������ͷŽ��
	                                           
	void CreatBinaryTree(char Array[]);              //���������
	int  Creat(BiTreeNode *T, int k,char Array[], int *i);  
	
	void Release(BiTreeNode*pNode);                  //�ͷź���

	int PreTraverse(BiTreeNode *pNode);              //����������ݹ�ʵ��
	int InTraverse(BiTreeNode*pNode);                //����������ݹ�ʵ��
   	int PostTraverse(BiTreeNode*pNode);              //����������ݹ�ʵ��
	void PreOrderTra(BiTreeNode*pNode);              //����������ǵݹ�ʵ��
	void InOrderTra(BiTreeNode *pNode);              //����������ǵݹ�ʵ��
	void PostOrderTra(BiTreeNode *pNode);            //����������ǵݹ�ʵ��
	void LayerTraverse(BiTreeNode *pNode);           //�������

	BiTreeNode* root;

};




#endif // !BI_TREE_H

