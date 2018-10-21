#include<stdio.h>
#ifndef BI_TREE_H
#define BI_TREE_H

struct BiTreeNode              
{
	char e;                   //数据域
	BiTreeNode* lchild;       //左孩子
	BiTreeNode* rchild;       //右孩子

};

struct BiTreeNodeFlag          //后序遍历需要，增加访问标志
{
	BiTreeNode *Node; 
	int Flag = 0;
};


//二叉树的类，涵盖树的相关操作
class BinaryTree
{
public :
	BinaryTree() { root=NULL; }
	~BinaryTree() { Release(root); }                //析构函数，释放结点
	                                           
	void CreatBinaryTree(char Array[]);              //构造二叉树
	int  Creat(BiTreeNode *T, int k,char Array[], int *i);  
	
	void Release(BiTreeNode*pNode);                  //释放函数

	int PreTraverse(BiTreeNode *pNode);              //先序遍历，递归实现
	int InTraverse(BiTreeNode*pNode);                //中序遍历，递归实现
   	int PostTraverse(BiTreeNode*pNode);              //后序遍历，递归实现
	void PreOrderTra(BiTreeNode*pNode);              //先序遍历，非递归实现
	void InOrderTra(BiTreeNode *pNode);              //中序遍历，非递归实现
	void PostOrderTra(BiTreeNode *pNode);            //后序遍历，非递归实现
	void LayerTraverse(BiTreeNode *pNode);           //层序遍历

	BiTreeNode* root;

};




#endif // !BI_TREE_H

