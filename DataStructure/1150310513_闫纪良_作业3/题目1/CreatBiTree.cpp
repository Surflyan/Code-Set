
/*本程序是根据已有先序和中序序列唯一生成一棵二叉树
  和根据已有中序和后序序列唯一生成一棵二叉树的构造程序
  经验证根据先序和后序序列并不能唯一确定一棵二叉树*/

//2016.12.3

#include <iostream>
#include <string>

using namespace std;
struct TreeNode
{
	 struct TreeNode * lchild;
     struct TreeNode * rchild;
	 char  data;
};

void PreOrederTraverse(TreeNode *T)
{
	if (T != NULL)
	{
		cout << T->data<<' ';
		PreOrederTraverse(T->lchild);
		PreOrederTraverse(T->rchild);

	}
}

void inOrderTraverse(TreeNode * T)
{
	if (T != NULL)
	{

		inOrderTraverse(T->lchild);
		cout << T->data<<' ';
		inOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(TreeNode * T)
{
	if (T != NULL)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data << ' ';
	}
}

//根据先序和中序序列递归建立二叉树
TreeNode* BinaryTreeFromOrderings(char* inOrder, char* preorder, int length)
 {
	   if (length == 0)return NULL;
			      
        TreeNode* node = new TreeNode;
        node->data = *preorder;
	    int rootIndex = 0;
        for (; rootIndex < length; rootIndex++)
	   {
		   if (inOrder[rootIndex] == *preorder)
		      break;
	    }
	 
	   node->lchild=BinaryTreeFromOrderings(inOrder, preorder + 1, rootIndex);
	   node->rchild= BinaryTreeFromOrderings(inOrder + rootIndex + 1, preorder + rootIndex + 1, length - (rootIndex + 1));

	   return node;
 }

//根据中序和后序序列递归建立二叉树
TreeNode* BinaryTree(char* inOrder, char* postOrder, int length)
{
	if (length == 0)return NULL;
	TreeNode* node = new TreeNode;
	node->data = *(postOrder + length - 1);
	int rootIndex = 0;
	for (; rootIndex < length; rootIndex++)
	{
		if (inOrder[rootIndex] == *(postOrder + length - 1))
			break;
	}
    node->lchild = BinaryTree(inOrder, postOrder, rootIndex);
	node->rchild = BinaryTree(inOrder + rootIndex + 1, postOrder + rootIndex, length - (rootIndex + 1));

	return node;
}

int main()
{   
	//给定先中后序列
    char* preOrder = "GDAFEMHZ";
	char* inOrder = "ADEFGHMZ";
    char* postOrder = "AEFDHZMG";
	TreeNode *T;

   //测试程序
	T=BinaryTreeFromOrderings(inOrder,preOrder, 8);
	PostOrderTraverse(T);
	cout << endl;
	T=BinaryTree(inOrder, postOrder, 8);
	PreOrederTraverse(T);
	cout << endl;
	printf("\n");
	return 0;
}
