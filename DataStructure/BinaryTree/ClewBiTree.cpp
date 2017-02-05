#include <stdio.h>
#include <iostream>
#include "ClewBiTree.h"

using namespace std;

//�����������ͨ������������
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
	if (ClewCreat(root, 1, Array, &i))         // ���������������
	{
		i++;                         
		ClewCreat(root, 2, Array, &i);           // ���������������
	}
	                               
}

//�ͷŶ�����
void ClewBiTree::Release(ClewBiTreeNode *pNode)
{
	if (pNode->Lflag==0)
	{   
		Release(pNode->lchild);
		Release(pNode->rchild);
		
		delete pNode;
	}

}


ClewBiTreeNode *Pre;                       //ȫ�ֽ�㣬��¼ǰ�����
void ClewBiTree::InThreading(ClewBiTreeNode *pNode)
{
	if (pNode)
	{
		InThreading(pNode->lchild);        //������������
		if (!pNode->lchild)
		{
			pNode->Lflag = 1;
			pNode->lchild = Pre;           //����������,ָ��ǰ��
		}
		if (!Pre->rchild)
		{
			Pre->Rflag = 1;
			Pre->rchild = pNode;           //�������Һ��ӣ�ָ����
		}
		Pre = pNode;                       //����ǰ�����
		InThreading(Pre->rchild);          //������������

	}
}
int ClewBiTree::InOrderThreading(ClewBiTreeNode *pNode, ClewBiTreeNode *root)
{

	pNode->rchild = pNode;          //��ָ����
	pNode->Rflag = 0;

	if (!root)
	{
		pNode->lchild = pNode;
		pNode->Lflag = 1;          //ָ���Լ�
	}
	else
	{
		pNode->lchild = root;
		Pre = pNode;
		InThreading(root);          //������
		Pre->rchild = pNode;        //β���ָ��ptr  ��ͷ
		Pre->Rflag = 1;

	}

	return 0;
}

//������������������ĺ�̽��
ClewBiTreeNode* ClewBiTree::InNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *temp;
	temp = pNode->rchild;             
	if (pNode->Rflag == 0)                  //���ұ�־Ϊ��¼��Ϊ��̣��Һ��Ӽ�Ϊ���
		while (temp->Lflag == 0)            //�����������ڣ���������������Ϊ���
			temp = temp->lchild;
	return temp;
}

//�ǵݹ������������������������
int ClewBiTree::InTraverse(ClewBiTreeNode*root)
{
	ClewBiTreeNode *temp;
	temp = root;
	do
	{
		temp = InNext(temp);                  //���α�������
		if (temp != root)
		{
			cout << temp->e << ' ';
		}
	} while (temp != root);
	cout << endl;
	return 0;
}

//������������������ĺ�̽��
ClewBiTreeNode *ClewBiTree::PreNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *temp;
	if (pNode->Lflag == 0)
		temp = pNode->lchild;         //������Ӵ��ڣ�������Ӽ�Ϊ��̣�
	else
	{
		temp = pNode;
		while (temp->Rflag == 1)        //���Ҿ��գ������е�һ�����Һ��ӵĽ�㼴Ϊ��̣�
			temp = temp->rchild;
		temp = temp->rchild;          //�������յ�����������ʱ��p��rchildΪ��̣�
	}
	return temp;
}
//�ǵݹ������������������������
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


//�����������ָ�����pNode�ĸ��ڵ㣬������*parent;
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

//������������������ĺ�̽��
ClewBiTreeNode *ClewBiTree::PostNext(ClewBiTreeNode *pNode)
{
	ClewBiTreeNode *Q=NULL;
	ClewBiTreeNode *t;
	if (!FindParent(this->root, Q, pNode))
	{  
		return NULL;                    //���ڵ��޺�̣����ؿ�
	}
	if (Q->lchild == pNode)
	{
		if (Q->Rflag == 1)              //�ýڵ�Ϊ���ӣ��������ֵܣ����ڵ㼴Ϊ���
			return Q;
		else
		{
			t = Q->rchild;
			do 
			{
	          while (t->Lflag == 0)       //�ý��Ϊ���ӣ������ֵܣ����ֵܵ���������Ҽ�Ϊ���
				t = t->lchild;
			  if (t->Rflag == 0)
				  t = t->rchild;
			} while (t->Lflag == 0 || t->Rflag == 0);

			return t;
		}
	}
	else                             //�ýڵ�Ϊ�Һ��ӣ��򸸽ڵ㼴Ϊ���
	{
		return Q;
	}
		
}


////�ǵݹ����������������ĺ������
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