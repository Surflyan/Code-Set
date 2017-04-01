// 2017.3.22
// Yan Jiliang
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#define T char


using namespace std;


struct Node
{
	T data;
	Node *lchild;
	Node *rchild;

	int left_flag;
	int right_flag;

};



#endif 