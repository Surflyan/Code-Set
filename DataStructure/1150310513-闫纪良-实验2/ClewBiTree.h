#include<stdio.h>
#ifndef CLEW_TREE
#define CLEW_TREE

struct ClewBiTreeNode              //�������ڵ�
{
	char e;                          
	ClewBiTreeNode *lchild;
	ClewBiTreeNode *rchild;
	int Lflag=0;
	int Rflag=0;
};

class ClewBiTree
{
public:
	ClewBiTree() { root = NULL; };
	~ClewBiTree() { Release(this->root); };         //�����������ͷŽڵ�

	void CreatBiTree(char Array[]);
	int  ClewCreat(ClewBiTreeNode *T, int k, char Array[], int *i);   //���������
	void Release(ClewBiTreeNode *pNode);                              //���ٶ�����

	void InThreading(ClewBiTreeNode *pNode);
	int InOrderThreading(ClewBiTreeNode *pNode, ClewBiTreeNode * tNode);   //����������������
	
	ClewBiTreeNode* InNext(ClewBiTreeNode *pNode);                      //����������Һ�̽��
	ClewBiTreeNode* PreNext(ClewBiTreeNode *pNode);                     //����������Һ�̽��
    ClewBiTreeNode *PostNext(ClewBiTreeNode *pNode);                    //����������Һ�̽��
	int FindParent(ClewBiTreeNode *root, ClewBiTreeNode *&parent ,ClewBiTreeNode *pNode);    //���Ҹ��ڵ�
	int InTraverse(ClewBiTreeNode*pNode);                               //�����������ǵݹ��������
	int PreTraverse(ClewBiTreeNode *pNode);                             //�����������ǵݹ��������
	int PostTraverse(ClewBiTreeNode *pNode);                            //�����������ǵݹ�������
	
	ClewBiTreeNode *root;                        //���ڵ�
};


#endif