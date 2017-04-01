#ifndef TREE_FOREST_H
#define TREE_FOREST_H

#define T char
#define MaxNumNode 20       //Max num tree node

class CSBinaryTree;

//help to solve input problem
struct ParentData
{
	int pindex;
	T data;
};

// edge node
struct CTNode
{
	int child;
	CTNode * next;
};

// head node
struct Box
{
	T data;
	CTNode * first_child = NULL;

};

//adjacency 
struct CTree
{
	Box nodes[MaxNumNode];
	int num_node;

};

//child_sibling 
struct CSNode
{
	T data;
	CSNode *first_child, *next_sibling;
};

//include build forest operation and some binary tree transform to forest
class Forest
{
public:
	Forest() {};
	int BuildForest();
	int BinaryTreeToTree(CSNode *root, CTree &tree_node, int &current_index, int &parent_index);
	int BinaryTreeToForest(CSBinaryTree &CSTree);
	int SetNodeData(CSNode *root, Box nodes[], int &node_index);
	int OutputPreOrder();

	CTree * ctree_;             //point to an array include num_tree tree ;
	int num_tree_;
};


class CSBinaryTree
{
public:
     	CSBinaryTree() {};
		~CSBinaryTree() { //ReleaseBinaryTree(cs_root_);
		}
		CSNode* TreeToBinary(CTree &root);
		int  ForestToTree(Forest F);
		int PreTraverse(CSNode *root);
		void ReleaseBinaryTree(CSNode *root);

		CSNode *cs_root_;
		int num_tree_;

	};
#endif
