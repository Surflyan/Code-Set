#include <iostream>
#include <stack>
#include "tree_forest.h"

using namespace std;

//according input build forest
//adjacency list to storge every tree
//return tree's number of this forest
int Forest::BuildForest()
{
	cout << "������ɭ����������Ŀ��" << endl;
	cin >> this->num_tree_;
	this->ctree_ = new CTree[num_tree_];

	int tree_index = 0;
	for (tree_index = 0; tree_index < num_tree_; tree_index++)
	{
		cout << "������� " << tree_index + 1 << " �������������ʽ#������" << endl;

		stack<ParentData> S;
		int node_index = 0;
		int parent_index = -1;
		ParentData P;
		T ch = 'a';

		int num_sibling = 0;
		while (ch != '#')
		{
			cin >> ch;
			if (ch == '#')
				break;
			if (ch == '(')
			{
				P.pindex = parent_index;
				P.data = ch;
				S.push(P);
				parent_index += num_sibling;

				num_sibling = 0;
			}
			else if (ch == ')' && !S.empty())
			{
				do
				{
					P = S.top();
					S.pop();
					parent_index = P.pindex;

				} while (P.data != '(');

			}
			else
			{
				ctree_[tree_index].nodes[node_index].data = ch;

				P.data = ch;
				P.pindex = parent_index;
				S.push(P);

				num_sibling++;

				if (parent_index != -1)
				{
					CTNode *pnode = ctree_[tree_index].nodes[parent_index].first_child;
					if (pnode == NULL)
					{
						ctree_[tree_index].nodes[parent_index].first_child = new CTNode;
						ctree_[tree_index].nodes[parent_index].first_child->child = node_index;
						ctree_[tree_index].nodes[parent_index].first_child->next = NULL;
					}
					else
					{
						while (pnode->next != NULL)
						{
							pnode = pnode->next;
						}
						pnode->next = new CTNode;
						pnode->next->child = node_index;
						pnode->next->next = NULL;
					}
				}
				node_index++;
			}
		}
		ctree_[tree_index].num_node = node_index;
	}
	return 0;
}


//use recursion to rebuild tree from binary tree
//���ý��������ӣ��������±�浽���ڵ�ĵ�һ���߽�㣬�ݹ�����
//���ýڵ���ڵ��������Һ��ӣ����Һ����±�浽�ý��߱�ĩβ���ݹ�����Һ��ӡ�
int Forest::BinaryTreeToTree(CSNode *root, CTree &tree_node, int &current_index, int &parent_index)
{
	CSNode *csnode = root->first_child;
	if (csnode != NULL)
	{
		current_index++;
		parent_index++;
		tree_node.nodes[parent_index].first_child = new CTNode;

		CTNode *ctnode = tree_node.nodes[parent_index].first_child;
		ctnode->child = current_index;
		ctnode->next = NULL;

		BinaryTreeToTree(csnode, tree_node, current_index, parent_index);

		CSNode *right_node = csnode->next_sibling;
		while (right_node != NULL)
		{
			current_index++;
			ctnode->next = new CTNode;
			ctnode->next->child = current_index;
			ctnode->next->next = NULL;
			ctnode = ctnode->next;
			right_node = right_node->next_sibling;
			if (right_node != NULL)
				BinaryTreeToTree(right_node, tree_node, current_index, parent_index);
		}
	}
	return 0;
}

//�������еĶ�����ת��Ϊ��ǰforest���ڽӱ�洢��ʽ
//���������ɭ�������ĸ����������������ĸ�ָ���Һ��Ӷ�Ϊɭ�����ĸ����
//�ȵ���SetNodeData ��������ÿ�����������ȴ����ڽӱ��ͷ����
//���ö�����ת�����������ν�ÿ��������ת����

int Forest::BinaryTreeToForest(CSBinaryTree &CSTree)
{
	this->num_tree_ = CSTree.num_tree_;
	this->ctree_ = new CTree[num_tree_];

	CSNode *csnode = CSTree.cs_root_;
	CSNode* sibling_csnode;
	int j = 0;
	while (csnode != NULL)
	{
		int i = 0;
		sibling_csnode = csnode->next_sibling;
		ctree_[j].nodes[i].data = csnode->data;
		SetNodeData(csnode->first_child, ctree_[j].nodes, ++i);
		ctree_[j].num_node = i;
		csnode->next_sibling = NULL;              //�ض�������

		int current_index = 0;
		int parent_index = -1;
		BinaryTreeToTree(csnode, ctree_[j], current_index, parent_index);
		csnode = sibling_csnode;
		j++;
	}

	return 0;

}

//���������Ľ����Ϣ�浽�������
int Forest::SetNodeData(CSNode *root, Box nodes[], int &node_index)
{
	if (root)
	{
		nodes[node_index++].data = root->data;
		SetNodeData(root->first_child, nodes, node_index);
		SetNodeData(root->next_sibling, nodes, node_index);
	}
	return 0;
}

int Forest::OutputPreOrder()
{
	int i = 0;
	while (i < num_tree_)
	{
		cout << "�� " << i + 1 << " ����:" << endl;
		int j = 0;
		while (j < ctree_[i].num_node)
		{
			cout << ctree_[i].nodes[j++].data << " ";

		}

		cout << endl;
		i++;
	}
	return 0;
}


//������tree root
//���أ�binary tree root
//�������Ľ��������������������飬������ÿ����������
//�����ڽӱ�����first child ��ΪNULL�����ݴ����Ķ������飬����Ӧ���ڵ������ָ��first child
// ����first child ->next ��ΪNULL, ��first child �������ڶ����������Һ���ָ���䣬 �����ж�next ��

CSNode* CSBinaryTree::TreeToBinary(CTree &root)
{
	int num_node = root.num_node;
	CSNode *cs_node = new CSNode[num_node];

	int i = 0;
	while (i <num_node)
	{
		cs_node[i].data = root.nodes[i].data;
		cs_node[i].first_child = NULL;
		cs_node[i].next_sibling = NULL;
		i++;
	}
	i = 0;

	while (i<num_node)
	{

		if (root.nodes[i].first_child != NULL)
		{
			int first_child = root.nodes[i].first_child->child;
			cs_node[i].first_child = &cs_node[first_child];               //note
			CTNode *ctnode = root.nodes[i].first_child->next;
			CSNode *csnode = cs_node[i].first_child;
			while (ctnode != NULL)
			{
				csnode->next_sibling = &cs_node[ctnode->child];

				csnode = csnode->next_sibling;
				ctnode = ctnode->next;
			}
			csnode->next_sibling = NULL;
		}
		else
			cs_node[i].first_child = NULL;
		i++;
	}
	return &cs_node[0];
}

//��ɭ��ת������������TreeToBinary��������ת��Ϊ�������������ӵ�cs_root->sibling .
int CSBinaryTree::ForestToTree(Forest F)
{
	this->num_tree_ = F.num_tree_;

	int i = 0;
	this->cs_root_ = TreeToBinary(F.ctree_[i++]);
	CSNode *csnode = cs_root_;
	while (i < num_tree_)
	{
		csnode->next_sibling = TreeToBinary(F.ctree_[i++]);
		csnode = csnode->next_sibling;
	}
	return 0;
}


int CSBinaryTree::PreTraverse(CSNode *root)
{
	if (root)
	{
		cout << root->data << " ";
		PreTraverse(root->first_child);
		PreTraverse(root->next_sibling);
	}
	return 0;
}

void CSBinaryTree::ReleaseBinaryTree(CSNode *root)
{
	if (root)
	{
		ReleaseBinaryTree(root->first_child);

		ReleaseBinaryTree(root->next_sibling);
		delete root;
	}

}


int main()
{
	Forest F1, F2;
	CSBinaryTree BT1, BT2;

	cout << "����ɭ��F1:" << endl;
	F1.BuildForest();

	cout << endl << "ɭ�� F1 ת ������ BT1��" << endl;
	BT1.ForestToTree(F1);
	BT1.PreTraverse(BT1.cs_root_);
	cout << endl;

	cout << endl << "������ BT1 ת ɭ�� F2��" << endl;
	F2.BinaryTreeToForest(BT1);
	F2.OutputPreOrder();

	cout << endl << "ɭ�� F2 ת ������ BT2��" << endl;
	BT2.ForestToTree(F2);
	BT2.PreTraverse(BT2.cs_root_);
	cout << endl;
	return 0;
}