#ifndef AVL_H
#define AVL_H

typedef int datatype  ;
typedef struct Node
{
	datatype data;             //数据
	Node* lchild;
	Node* rchild;
	int height;               //该节点的高度

}Node;

extern Node* SearchNode(Node* T, datatype key);
extern Node* InsertNode(Node* T, datatype key);
extern Node* DeleteNode(Node*T, datatype key);
extern void InOrderSort(Node* Node);
extern void TreePrint(Node *T, int level);
extern void DestroyTree(Node* root);
#endif;