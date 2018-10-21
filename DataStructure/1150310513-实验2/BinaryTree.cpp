#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include "BiTree.h"
#include "ClewBiTree.h"

using namespace std;

/*ͨ��������������еݹ鷨���������
  pNode :��ǰ���ڵ�    k ����������־��Array���������� ��int i,��������*/
int BinaryTree::Creat(BiTreeNode *pNode, int k, char Array[], int*i)
{   
	BiTreeNode *tNode=new BiTreeNode;
	if (Array[*i] == '#')                                  //���н�����־
		return 0;
	if (Array[*i] != '$')                                  //������Ϊ��
	{
		tNode->e = Array[*i];
		tNode->lchild = NULL;
		tNode->rchild = NULL;

		if (k == 1)
			pNode->lchild = tNode;
		if (k == 2)
			pNode->rchild = tNode;
		
		(*i)++;
		if (!Creat(tNode, 1, Array, i))                      //����������
			return 0;
		(*i)++;
		if (!Creat(tNode, 2, Array, i))                       //����������
			return 0;
	}
	return 1;

}
//ͨ���������н���������������������������
void BinaryTree::CreatBinaryTree(char Array[])
{
	int i = 0;
	root = new BiTreeNode;
	root->e = Array[i];                        //�������ڵ�
	root->lchild = NULL;
	root->rchild = NULL;
	i++;
	if (Creat(root, 1, Array, &i))             //����������
	{
    i++;                        
	Creat(root, 2, Array, &i);                 // ����������
	}
	                                         
}

//�ݹ��ͷŽ��
void BinaryTree::Release(BiTreeNode *pNode)
{  
	if (pNode)
	{
    Release(pNode->rchild);
	Release(pNode->lchild);
	delete pNode;
	}
	
}

//�ݹ��������
int BinaryTree::PreTraverse(BiTreeNode *pNode)
{
	if (pNode)
	{
		cout << pNode->e << ' ';
		PreTraverse(pNode->lchild);
		PreTraverse(pNode->rchild);
	}
	
	return 0;
}

//�ݹ��������
int BinaryTree::InTraverse(BiTreeNode*pNode)
{
	if (pNode)
	{
		
		InTraverse(pNode->lchild);
		cout << pNode->e << ' ';
		InTraverse(pNode->rchild);
	}
	
	return 0;
}
//�ݹ�������
int BinaryTree::PostTraverse(BiTreeNode*pNode)
{
	if (pNode)
	{

		PostTraverse(pNode->lchild);
	    PostTraverse(pNode->rchild);
		cout << pNode->e << ' ';
	}
	
	return 0;
}

//�ǵݹ����������ͨ��ջ����
//  pNode�� root
void BinaryTree::PreOrderTra(BiTreeNode *pNode)
{   
	stack<BiTreeNode> S;                  //����ջ�ṹ S
	BiTreeNode *tNode = pNode;            
	while (tNode ||!S.empty())            //������||ջδ�ռ�������
	{
		if (tNode)
		{
			cout << tNode->e << ' ';         
			S.push(*tNode);                //ѹջ
			tNode = tNode->lchild;
		}
		else
		{   
			tNode = &(S.top());            //��ջ
			S.pop();
			tNode = tNode->rchild;
		}
	}
	cout << endl;
}

//�ǵݹ����������������ڵ�
void BinaryTree::InOrderTra(BiTreeNode *pNode)
{
	stack<BiTreeNode> S;
	BiTreeNode *tNode = pNode;
	while (tNode || !S.empty())
	{
		if (tNode)
		{
			
			S.push(*tNode);
			tNode = tNode->lchild;
		}
		else
		{
			tNode = &(S.top());
			S.pop();
			cout << tNode->e <<' ';
			tNode = tNode->rchild;
		}
	}
	cout << endl;
}
/*�ǵݹ��������������һ�����Flag����һ�η�����1���ڶ��η�����2
  ��Flag=2ʱ���������*/
void BinaryTree::PostOrderTra(BiTreeNode*pNode)
{
	BiTreeNodeFlag *temp;
	BiTreeNode *tNode = pNode;
	stack<BiTreeNodeFlag> T;
	while (tNode || !T.empty())
	{
		if (tNode)
		{
			BiTreeNodeFlag *pFnode = new BiTreeNodeFlag;
			pFnode->Node = tNode;
			pFnode->Flag = 1;                       //��һ�η��ʽ�FLag��Ϊ1��
			T.push(*pFnode);                        //ѹջ
			tNode = tNode->lchild;                  //����������
		}
		else
		{
			temp=&(T.top());                          //��ջ
			T.pop();
			if (temp->Flag == 1)
			{
				temp->Flag = 2;                        //�ڶ��η��ʣ�Flag��Ϊ2����ѹջ
				T.push(*temp);
				tNode = temp->Node->rchild;            //����������
			}
			else
			{
				cout << (temp->Node->e)<<' ';               //�����η��ʣ����
				tNode = NULL;
			}

		}
	}
	cout << endl;
}

//������������ö����Ƚ��ȳ�������
void BinaryTree::LayerTraverse(BiTreeNode*pNode)
{
	queue<BiTreeNode> Q;
	BiTreeNode *tNode = pNode;
	BiTreeNode rNode;
	if (tNode)
	{
		Q.push(*tNode);
		while (!Q.empty())
		{
			rNode = Q.front();
			Q.pop();
			cout << rNode.e << ' ';
			if (rNode.lchild)
			{
				  tNode = rNode.lchild;
                  Q.push(*tNode);
			}
			if (rNode.rchild)
			{
				tNode = rNode.rchild;
				Q.push(*tNode);
			}	
		}
	}
	cout << endl;
}


int main()
{
	char c;
	BinaryTree T;
	
	char Array[] = { "ABDH$$I$$E$$CF$J$$G$$"};
	cout << "�Ƿ��������� y/n��";
	cin >> c;
	if (c == 'y')
		T.CreatBinaryTree(Array);
	else
		return 0;
	cout << "�ݹ������y/s��";
	cin >> c;
	if (c == 'y')
	{
		cout << endl << "���������";
		T.PreTraverse(T.root);
		cout << endl;
		cout << "���������";
		T.InTraverse(T.root);
		cout << endl;
		cout << "���������";
		T.PostTraverse(T.root);
		cout << endl;
	}
	cout << "�ǵݹ���� �� y/n��";
	cin >> c;

	if (c == 'y')
	{
		cout << endl<<"�ǵݹ����������";
		T.PreOrderTra(T.root);
		cout << "�ǵݹ����������";
		T.InOrderTra(T.root);
		cout << "�ǵݹ���������";
		T.PostOrderTra(T.root);
		cout << "���������";
		T.LayerTraverse(T.root);
	}
	ClewBiTree B;
	ClewBiTreeNode *ptr = new ClewBiTreeNode;
	ClewBiTreeNode *P= new ClewBiTreeNode;
	cout << "�������ı����� y/n��";
	cin >> c;
	if (c == 'y')
	{
		B.CreatBiTree(Array);
		B.InOrderThreading(ptr, B.root);

		cout << "�������������������";
		B.PreTraverse(ptr);
		cout << "�������������������";
		B.InTraverse(ptr);
		cout << "�������������������";
		B.PostTraverse(ptr);
	}
	delete ptr;
	delete P;
}
