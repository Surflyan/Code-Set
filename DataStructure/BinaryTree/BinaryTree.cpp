#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include "BiTree.h"
#include "ClewBiTree.h"

using namespace std;

/*通过先序二叉树序列递归法建造二叉树
  pNode :当前根节点    k 左右子树标志，Array二叉树序列 ，int i,待放入结点*/
int BinaryTree::Creat(BiTreeNode *pNode, int k, char Array[], int*i)
{   
	BiTreeNode *tNode=new BiTreeNode;
	if (Array[*i] == '#')                                  //序列结束标志
		return 0;
	if (Array[*i] != '$')                                  //结点儿子为空
	{
		tNode->e = Array[*i];
		tNode->lchild = NULL;
		tNode->rchild = NULL;

		if (k == 1)
			pNode->lchild = tNode;
		if (k == 2)
			pNode->rchild = tNode;
		
		(*i)++;
		if (!Creat(tNode, 1, Array, i))                      //构造左子树
			return 0;
		(*i)++;
		if (!Creat(tNode, 2, Array, i))                       //构造右子树
			return 0;
	}
	return 1;

}
//通过先序序列建立二叉树，参数：二叉树序列
void BinaryTree::CreatBinaryTree(char Array[])
{
	int i = 0;
	root = new BiTreeNode;
	root->e = Array[i];                        //创建根节点
	root->lchild = NULL;
	root->rchild = NULL;
	i++;
	if (Creat(root, 1, Array, &i))             //创建左子树
	{
    i++;                        
	Creat(root, 2, Array, &i);                 // 创建右子树
	}
	                                         
}

//递归释放结点
void BinaryTree::Release(BiTreeNode *pNode)
{  
	if (pNode)
	{
    Release(pNode->rchild);
	Release(pNode->lchild);
	delete pNode;
	}
	
}

//递归先序遍历
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

//递归中序遍历
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
//递归后序遍历
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

//非递归先序遍历，通过栈操作
//  pNode： root
void BinaryTree::PreOrderTra(BiTreeNode *pNode)
{   
	stack<BiTreeNode> S;                  //声名栈结构 S
	BiTreeNode *tNode = pNode;            
	while (tNode ||!S.empty())            //结点存在||栈未空继续遍历
	{
		if (tNode)
		{
			cout << tNode->e << ' ';         
			S.push(*tNode);                //压栈
			tNode = tNode->lchild;
		}
		else
		{   
			tNode = &(S.top());            //弹栈
			S.pop();
			tNode = tNode->rchild;
		}
	}
	cout << endl;
}

//非递归中序遍历，传入根节点
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
/*非递归后序遍历，给结点一个标记Flag，第一次访问置1；第二次访问置2
  当Flag=2时，遍历输出*/
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
			pFnode->Flag = 1;                       //第一次访问将FLag置为1；
			T.push(*pFnode);                        //压栈
			tNode = tNode->lchild;                  //遍历左子树
		}
		else
		{
			temp=&(T.top());                          //出栈
			T.pop();
			if (temp->Flag == 1)
			{
				temp->Flag = 2;                        //第二次访问，Flag置为2，再压栈
				T.push(*temp);
				tNode = temp->Node->rchild;            //遍历右子树
			}
			else
			{
				cout << (temp->Node->e)<<' ';               //第三次访问，输出
				tNode = NULL;
			}

		}
	}
	cout << endl;
}

//层序遍历，运用队列先进先出的特性
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
	cout << "是否生成树？ y/n：";
	cin >> c;
	if (c == 'y')
		T.CreatBinaryTree(Array);
	else
		return 0;
	cout << "递归遍历？y/s：";
	cin >> c;
	if (c == 'y')
	{
		cout << endl << "先序遍历：";
		T.PreTraverse(T.root);
		cout << endl;
		cout << "中序遍历：";
		T.InTraverse(T.root);
		cout << endl;
		cout << "后序遍历：";
		T.PostTraverse(T.root);
		cout << endl;
	}
	cout << "非递归遍历 ？ y/n：";
	cin >> c;

	if (c == 'y')
	{
		cout << endl<<"非递归先序遍历：";
		T.PreOrderTra(T.root);
		cout << "非递归中序遍历：";
		T.InOrderTra(T.root);
		cout << "非递归后序遍历：";
		T.PostOrderTra(T.root);
		cout << "层序遍历：";
		T.LayerTraverse(T.root);
	}
	ClewBiTree B;
	ClewBiTreeNode *ptr = new ClewBiTreeNode;
	ClewBiTreeNode *P= new ClewBiTreeNode;
	cout << "线索树的遍历？ y/n：";
	cin >> c;
	if (c == 'y')
	{
		B.CreatBiTree(Array);
		B.InOrderThreading(ptr, B.root);

		cout << "中序线索树先序遍历：";
		B.PreTraverse(ptr);
		cout << "中序线索树中序遍历：";
		B.InTraverse(ptr);
		cout << "中序线索树后序遍历：";
		B.PostTraverse(ptr);
	}
	delete ptr;
	delete P;
}
