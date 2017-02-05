#include<stdio.h>
#ifndef CLEW_TREE
#define CLEW_TREE

struct ClewBiTreeNode              //线索树节点
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
	~ClewBiTree() { Release(this->root); };         //析构函数，释放节点

	void CreatBiTree(char Array[]);
	int  ClewCreat(ClewBiTreeNode *T, int k, char Array[], int *i);   //构造二叉树
	void Release(ClewBiTreeNode *pNode);                              //销毁二叉树

	void InThreading(ClewBiTreeNode *pNode);
	int InOrderThreading(ClewBiTreeNode *pNode, ClewBiTreeNode * tNode);   //二叉树中序线索化
	
	ClewBiTreeNode* InNext(ClewBiTreeNode *pNode);                      //中序遍历查找后继结点
	ClewBiTreeNode* PreNext(ClewBiTreeNode *pNode);                     //先序遍历查找后继结点
    ClewBiTreeNode *PostNext(ClewBiTreeNode *pNode);                    //后序遍历查找后继结点
	int FindParent(ClewBiTreeNode *root, ClewBiTreeNode *&parent ,ClewBiTreeNode *pNode);    //查找父节点
	int InTraverse(ClewBiTreeNode*pNode);                               //中序线索树非递归中序遍历
	int PreTraverse(ClewBiTreeNode *pNode);                             //中序线索树非递归先序遍历
	int PostTraverse(ClewBiTreeNode *pNode);                            //中序线索树非递归后序遍历
	
	ClewBiTreeNode *root;                        //根节点
};


#endif