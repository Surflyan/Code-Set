
/*�������Ǹ��������������������Ψһ����һ�ö�����
  �͸�����������ͺ�������Ψһ����һ�ö������Ĺ������
  ����֤��������ͺ������в�����Ψһȷ��һ�ö�����*/

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

//����������������еݹ齨��������
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

//��������ͺ������еݹ齨��������
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
	//�������к�����
    char* preOrder = "GDAFEMHZ";
	char* inOrder = "ADEFGHMZ";
    char* postOrder = "AEFDHZMG";
	TreeNode *T;

   //���Գ���
	T=BinaryTreeFromOrderings(inOrder,preOrder, 8);
	PostOrderTraverse(T);
	cout << endl;
	T=BinaryTree(inOrder, postOrder, 8);
	PreOrederTraverse(T);
	cout << endl;
	printf("\n");
	return 0;
}
