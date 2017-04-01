// 实现二叉树的建立、先序线索化以及后序线索化
// 依据线索分别先序遍历、后序遍历
// 后序遍历，线索对结点后继的确定没有帮助

#include <iostream>
#include "binary_tree.h"

using namespace std;

//根据先序序列递归建立二叉树
//参数：根指针，序列数组，下标引用
// 返回根节点
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
//先序线索化二叉树
//1.如果二叉链表root为空，则返回；否则
//2 对结点root建立线索；
//   2.1  若root没有左右孩子，则将root左右标志置为False；
//   2.2  若结点pre右标志为False，则为pre加上后继线索；
//   2.3  若root没有左孩子，则为root加上前驱线索; 
//   2.4  令pre指向刚刚访问的结点root； 
//3 对root的左子树建立线索；
//4 对root的右子树建立线索。
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
//先序线索树某结点的后继结点查找
Node* PreNext(Node *&root)
{
	Node *p;
	p = root;
	if (p->left_flag == true)            //左孩子存在，左孩子即为后继
		return p->lchild;
	else 
		return p->rchild;                //左孩子不存在，右节点即为后继

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

//后序线索化二叉树
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

// 查找二叉树某一结点的父节点
//参数: 根节点，存放父节点指针，查找的结点
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
//后序线索树后继节点的查找
//参数: 根节点，待查找结点
// 1 若cur_node是根，则cur_node是该二叉树后序遍历过程中最后一个访问到的结点。cur_node的后序后继为空
// 2 若cur_node是其双亲的右孩子，则cur_node的后序后继结点就是其双亲结点
// 3 若cur_node是其双亲的左孩子，但cur_node无右兄弟，cur_node的后序后继结点是其双亲结点
// 4 若cur_node是其双亲的左孩子，但cur_node有右兄弟，则cur_node的后序后继是其双亲的右子树中
//    第一个后序遍历到的结点，它是该子树中"最左下的叶结点"
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
	
	cout << "先序线索树先序序列：" << endl;
	PreOrderThreading(T1);
	ShowPreOrderThreading(T1);
	ReleaseBinaryTree(T1);

	i = 0;
	CreatBinaryTree(T2, node_array, i);
	cout << "后序线索树后续序列；" << endl;
	PostOrderThreading(T2);
	ShowPostOrderThreading(T2);
	ReleaseBinaryTree(T2);
}
