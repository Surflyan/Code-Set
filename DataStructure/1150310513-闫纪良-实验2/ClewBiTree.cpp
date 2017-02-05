#include <stdio.h>
#include <iostream>
#include "ClewBiTree.h"

using namespace std;

//构造二叉树，通过二叉树序列
int ClewBiTree::ClewCreat(ClewBiTreeNode *pNode, int k, char Array[], int*i)
{
	ClewBiTreeNode *tNode = new ClewBiTreeNode;
	if (Array[*i] == '#')
		return 0;
	if (Array[*i] != '$')
	{
		tNode->e = Array[*i];
		tNode->lchild = NULL;
		tNode->rchild = NULL;

		if (k == 1)
			pNode->lchild = tNode;
		if (k == 2)
			pNode->rchild = tNode;

		(*i)++;
		if (!ClewCreat(tNode, 1, Array, i))
			return 0;
		(*i)++;
		if (!ClewCreat(tNode, 2, Array, i))
			return 0;
	}
	return 1;
}

void ClewBiTree::CreatBiTree(char Array[])
{
	int i = 0;
	root = new ClewBiTreeNode;
	root->e = Array[i];
	root->lchild = NULL;
	root->rchild = NULL;
	i++;
	if (ClewCreat(root, 1, Array, &i))         // 创建根结点左子树
	{
		i++;                         
		ClewCreat(root, 2, Array, &i);           // 创建根结点右子树
	}
	                               
}

//释放二叉树
void ClewBiTree::Release(ClewBiTreeNode *pNode)
{
	if (pNode->Lflag==0)
	{   
		Release(pNode->lchild);
		Release(pNode->rchild);
		
		delete pNode;
	}

}


ClewBiTreeNode *Pre;                       //全局结点，纪录前驱结点
void ClewBiTree::InThreading(ClewBiTreeNode *pNode)
{
	if (pNode)
	{
		InThreading(pNode->lchild);        //线索化左子树
		if (!pNode->lchild)
		{
			pNode->Lflag = 1;
			pNode->lchild = Pre;           //线索化左孩子,指向前驱
		}
		if (!Pre->rchild)
		{
			Pre->Rflag = 1;
			Pre->rchild = pNode;           //线索化右孩子，指向后继
		}
		Pre = pNode;                       //更新前驱结点
		InThreading(Pre->rchild);          //线索化右子树

	}
}
int ClewBiTree::InOrderThreading(ClewBiTreeNode *pNode, ClewBiTreeNode *root)
{

	pNode->rchild = pNode;          //先指向本身
	pNode->Rflag = 0;

	if (!root)
	{
		pNode->lchild = pNode;
		pNode->Lflag = 1;          //指向自己
	}
	else
	{
		pNode->lchild = root;
		Pre = pNode;
		InThreading(root);          //线索化
		Pre->rchild = pNode;        //尾结点指向ptr  空头
		Pre->Rflag = 1;

	}

	return 0;
}

//中序线索树中序遍历的后继结点
ClewBiTreeNode* ClewBiTree::InNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *temp;
	temp = pNode->rchild;             
	if (pNode->Rflag == 0)                  //若右标志为纪录的为后继；右孩子即为后继
		while (temp->Lflag == 0)            //若右子树存在，右子树的最左孩子为后继
			temp = temp->lchild;
	return temp;
}

//非递归中序线索二叉树的中序遍历
int ClewBiTree::InTraverse(ClewBiTreeNode*root)
{
	ClewBiTreeNode *temp;
	temp = root;
	do
	{
		temp = InNext(temp);                  //依次遍历求后继
		if (temp != root)
		{
			cout << temp->e << ' ';
		}
	} while (temp != root);
	cout << endl;
	return 0;
}

//中序线索树先序遍历的后继结点
ClewBiTreeNode *ClewBiTree::PreNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *temp;
	if (pNode->Lflag == 0)
		temp = pNode->lchild;         //若左儿子存在，则左儿子即为后继；
	else
	{
		temp = pNode;
		while (temp->Rflag == 1)        //左右均空，右序列第一个有右孩子的结点即为后继；
			temp = temp->rchild;
		temp = temp->rchild;          //左子树空但右子树不空时，p的rchild为后继；
	}
	return temp;
}
//非递归中序线索二叉树的先序遍历
int ClewBiTree::PreTraverse(ClewBiTreeNode*root)
{
	ClewBiTreeNode *temp;
	temp = root;
	do
	{
		temp = PreNext(temp);
		if (temp != root)
		{
			cout << temp->e << ' ';
		}
	} while (temp != root);
	cout << endl;
	return 0;
}


//后序遍历查找指定结点pNode的父节点，保存在*parent;
int  ClewBiTree::FindParent(ClewBiTreeNode* root,ClewBiTreeNode *&parent,ClewBiTreeNode* pNode)
{
	int f = 0;
	ClewBiTreeNode *tNode = root;
	if (pNode == root)
		return 0;
	if (f==0)
	{   
		
		if(tNode->Lflag==0 &&f==0)
			FindParent(tNode->lchild,parent,pNode);

		if(tNode->Rflag==0 &&f==0)
			FindParent(tNode->rchild,parent,pNode);

		if (f == 0 && ((tNode->Lflag == 0 && tNode->lchild == pNode) 
			       || (tNode->Rflag == 0 && tNode->rchild == pNode)))
		{
			f = 1;
			parent = tNode;
			return 1;
		}
	}
	return 1;
}

//中序线索树先序遍历的后继结点
ClewBiTreeNode *ClewBiTree::PostNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *Q=NULL;
	ClewBiTreeNode *t;
	if (!FindParent(this->root, Q, pNode))
	{  
		return NULL;                    //根节点无后继，返回空
	}
	if (Q->lchild == pNode)
	{
		if (Q->Rflag == 1)              //该节点为左孩子，且无右兄弟，父节点即为后继
			return Q;
		else
		{
			t = Q->rchild;
			do 
			{
	          while (t->Lflag == 0)       //该结点为左孩子，有右兄弟，右兄弟的最左或最右即为后继
				t = t->lchild;
			  if (t->Rflag == 0)
				  t = t->rchild;
			} while (t->Lflag == 0 || t->Rflag == 0);

			return t;
		}
	}
	else                             //该节点为右孩子，则父节点即为后继
	{
		return Q;
	}
		
}


////非递归中序线索二叉树的后序遍历
int ClewBiTree::PostTraverse(ClewBiTreeNode*root)
{
	ClewBiTreeNode *temp=root;
	while(temp->Lflag==0)
	     temp = temp->lchild;
	cout << temp->e<<' ';
	do
	{
		temp =PostNext(temp);
		if (temp != NULL)
		{
			cout << temp->e<<' ';
		}
	} while (temp != NULL);
	cout << endl;
	return 0;
}