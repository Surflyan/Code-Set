#include<iostream>
#include "AVL.h"

using namespace std;


//生成新节点
Node* NewNode(datatype key)
{
	Node * rNode = new Node;
	rNode->data = key;
	rNode->lchild = NULL;
	rNode->rchild = NULL;
	rNode->height =0 ;
	return rNode;
}
//返回结点高度
int GetHeight(Node* pNode)
{
	return (pNode == NULL) ? -1 : pNode->height;
}

//返回大值
int Max(int a, int b)
{
	return a > b ? a : b;
}

/*     A                     B
      / \                   / \
	 B   C                 D   A
    / \                       / \
   D   E                     E   C
   h+1  h
*/
Node* LL_Rotate(Node* pNode)
{
	Node* tNode = pNode->lchild;
	pNode->lchild = tNode->rchild;
	tNode->rchild = pNode;
	pNode->height = Max(GetHeight(pNode->lchild), GetHeight(pNode->rchild))+1;
	tNode->height = Max(GetHeight(tNode->lchild), pNode->height)+1;
	return tNode;
	

}
Node* RR_Rotate(Node* pNode)
{
	Node* tNode = pNode->rchild;
	pNode->rchild = tNode->lchild;
	tNode->lchild = pNode;
	pNode->height = Max(GetHeight(pNode->lchild), GetHeight(pNode->rchild))+1;
	tNode->height = Max(GetHeight(tNode->lchild), pNode->height)+1;
	return tNode;
}

Node*LR_Rotate(Node* pNode)
{
	pNode->lchild = RR_Rotate(pNode->lchild);
	return LL_Rotate(pNode);

}

Node* RL_Rotate(Node* pNode)
{
	pNode->rchild = LL_Rotate(pNode->rchild);
	return RR_Rotate(pNode);
}

Node* InsertNode(Node* T,datatype key)
{
	if (T == NULL)
		return (T = NewNode(key));
	else if (key < T->data)
	{
		T->lchild = InsertNode(T->lchild, key);
	 }
	else if (key > T->data)
	{		
		T->rchild = InsertNode(T->rchild, key);
	}

	T->height = Max(GetHeight(T->lchild), GetHeight(T->rchild))+1;
	if (GetHeight(T->lchild) - GetHeight(T->rchild) == 2)
	{
		if (key < T->lchild->data)
			T = LL_Rotate(T);
		else
			T = LR_Rotate(T);
	}
	else if (GetHeight(T->rchild) - GetHeight(T->lchild) == 2)
	{
		if (key > T->rchild->data)
			T = RR_Rotate(T);
		else
			T = RL_Rotate(T);
	}
	return T; 
}

Node* DeleteNode(Node*T, datatype key)
{
	if (T == NULL) return NULL;
	if (key == T->data)
	{
		if (T->rchild == NULL)
		{
			Node *temp = T;
			T = T->lchild;
			delete temp;
			return T;
		}
		else
		{
			Node* temp = T->rchild;
			while (temp->lchild)
				temp = temp->lchild;
			T->data = temp->data;
			T->rchild = DeleteNode(T->rchild, temp->data);
		}
	}
	else if (key < T->data)
		T->lchild = DeleteNode(T->lchild, key);
	else
		T->rchild = DeleteNode(T->rchild, key);

	T->height = Max(GetHeight(T->lchild), GetHeight(T->rchild))+1;

	if (GetHeight(T->lchild) - GetHeight(T->rchild) == 2)
	{
		if (GetHeight(T->lchild->lchild) > GetHeight(T->lchild->rchild))
			T = LL_Rotate(T);
		else
			T = LR_Rotate(T);
	}
	else if (GetHeight(T->rchild) - GetHeight(T->lchild) == 2)
	{
		if (GetHeight(T->rchild->rchild) > GetHeight(T->rchild->lchild))
			T = RR_Rotate(T);
		else
			T = RL_Rotate(T);
	}
	return T;
}
Node* SearchNode(Node* T, datatype key)
{
	Node* pNode = T;
	if (pNode == NULL || key == pNode->data)
		return pNode;
	if (key < pNode->data)
		return(SearchNode(pNode->lchild, key));
	else
	    return (SearchNode(pNode->rchild, key));

}
void DestroyTree(Node* root)
{
	if (root == NULL) return;
	DestroyTree(root->lchild);
	DestroyTree(root->rchild);
	delete root;
}

void InOrderSort(Node* pNode)
{
	if (pNode!= NULL)
	{
		InOrderSort(pNode->lchild);
		cout << pNode->data << ' ';
		InOrderSort(pNode->rchild);
	}
}

void TreePrint(Node* T, int level)
{
	if (!T)                            //如果指针为空，返回上一层  
	{ 
		return;
	}
	TreePrint(T->rchild, level + 1);    //打印右子树，并将层次加1  
	for (int i = 0; i<level; i++)       //按照递归的层次打印空格  
	{
		printf("   ");
	}
	printf("%d\n", T->data);             //输出根结点  
	TreePrint(T->lchild, level + 1);     //打印左子树，并将层次加1  
}