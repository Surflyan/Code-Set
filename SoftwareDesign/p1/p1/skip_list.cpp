#include<iostream>
#include<stdlib.h>
#include<stdio.h>

#include <time.h>

using namespace std;

struct Node
{
	int data;
	int level;
	Node* next;
	Node* below;
};

class SkipList
{
public:
	SkipList()
	{
		head = new Node;
		head->data = -1;
		head->level = 0;
		head->next = NULL;
		head->below = NULL;

	}

	~SkipList() { ClearSkipList(); }
	bool InsertSkipList(int ele);
	int InitialSkipList();
	Node* HorizontalInsert(Node* vNode, int ele);
	int ShowSkipList();

	int SeekElement(int ele);
	Node* SeekHorizontalEle(Node *vertical_node, int ele);
    
	int DeleteElement(int ele);
	Node* DeleteHorizontalEle(Node * horizontal_head_node,int ele);

	int ClearHorizontalLineEle(Node * horizontal_head_node);
	int ClearSkipList();
private:
	Node *head;
	
};

int RandomLevel()
{
	int level = 0;

	for (;;)
	{
		if (rand() % 2 == 1)
		{
			level++;
		}
		else
			break;
		
	}

	return level;

}
//ͨ������RandomLevel���ɴ�����Ԫ��
//��level���ڵ�ǰ��������������Ӳ���
//���ش�����Ԫ�ز���
int SkipList::InitialSkipList()
{
	int l_level, t_level;
	Node *pnode = head;
	l_level = RandomLevel();
	t_level = l_level;
	while (t_level >=head->level)            //���±�ͷ
	{
		Node* tNode;
		tNode = new Node;
		tNode->data = -1;
		tNode->level = t_level;
		tNode->next = NULL;

		tNode->below = pnode->below;
		pnode->below= tNode;
		pnode = tNode;

		t_level--;
		
	}
	
	if(l_level>=head->level)
		head->level = l_level + 1;      //���±�ͷhead ����
	return l_level;
}
Node * NewNode()
{
	Node * tNode = new Node;
	tNode->data = -1;
	tNode->below = NULL;
	tNode->next = NULL;
	tNode->level = 0;

	return tNode;
}

// ������������Ԫ�أ�������ͷ
// ���մ�С���󣬲���Ԫ��
// ���ز���ڵ�ָ��
Node* SkipList::HorizontalInsert(Node *vNode, int ele)
{
	Node*pNode, *tNode, *rNode;
	pNode = vNode;
	tNode = vNode->next;

	while (tNode != NULL)
	{                                           //��������λ��
		if (tNode->data < ele)
		{
			pNode = pNode->next;
			tNode = tNode->next;
		}
		else
			break;
	}


	rNode = NewNode();
	rNode->data = ele;                           //������
	rNode->next = pNode->next;
	rNode->level = pNode->level;
    pNode->next = rNode;

	return rNode;
}

// ������ ������Ԫ��
// ���ó�ʼ�����������ش�Ԫ�����ڲ���
// �������£�һ�β���ÿ�㣻

bool SkipList::InsertSkipList(int ele)
{
	int level;
	level = InitialSkipList();                 // ȷ��Ԫ�����ڲ���
	Node * tNode, *rNode, *pNode ;
	tNode = head;
	while (tNode->level > level)
	{
		tNode = tNode->below;                 //�ӱ�ͷ�����ҵ���ʼ����Ĳ�
	}

	rNode = NULL;
	while (true)
	{
		pNode = HorizontalInsert(tNode, ele);    //���β���ÿ��
		if (rNode != NULL)
			rNode->below = pNode;            //���ϲ��Ԫ��ָ����һ��
		if (tNode->below != NULL)
		{
			tNode = tNode->below;
			rNode = pNode;
		}
		else
			break;

	}
	return true;
}

//��ʾ����
int SkipList::ShowSkipList()
{
	Node * pnode, *tnode;
	pnode = head;
	while (pnode->below != NULL)
	{   
		pnode = pnode->below;
	    
		cout << "�� " << pnode->level << " ��:";
		tnode = pnode->next;
		while (tnode!=NULL)
		{
			cout << tnode->data << "";
			tnode = tnode->next;
		}
		cout << endl;
	}
	return 0;

}

//���������������ı�ͷ��������ͬԪ�ص��²�Ԫ�أ� ����Ԫ��ֵ
//�����������������������Ԫ�ص���һ��
//��������������Ƚϵ�Ԫ�أ�������Ҳ�Ƚ�Ԫ��
Node * SkipList::SeekHorizontalEle(Node* vertical_node,int ele)
{
	Node*horizontal_node, *tnode;
	horizontal_node = vertical_node->next;
	tnode = vertical_node;
	if (horizontal_node == NULL || tnode->data==ele)            //����ǰ���������һ���ڵ�Ϊ��
	{                                                           //���ߵ�ǰ�����ڵ�ֵ������ֵ��ȣ���ֱ�������ǰ�ڵ�ֵ
		cout << "\n�� " << tnode->level << " �㣺" << tnode->data;
		return tnode->below;
	}

	while (horizontal_node != NULL)             //��������
	{
		if (horizontal_node->data > ele)
			break;
		cout << "\n�� " << horizontal_node->level << " �㣺 ";
		 if (horizontal_node->data == ele)
		{
			cout << horizontal_node->data;
			tnode = tnode->next;
			break;
		}
		else if (horizontal_node->data < ele)
		{
			cout << horizontal_node->data << " ";
			horizontal_node = horizontal_node->next;
			tnode = tnode->next;
		}

	}
	return tnode->below;
}

//����Ԫ�أ���������
int SkipList::SeekElement(int ele)
{
	Node *vertical_node;
	vertical_node = head->below;
	
	while (vertical_node != NULL)
	{
		vertical_node = SeekHorizontalEle(vertical_node,ele);
	}

	return 0;
}

//������ ɾ��������ʼ��㣬��ɾ��Ԫ��ֵ
//������Ҵ�ɾ��Ԫ�أ���ɾ��
//������ɾ��Ԫ��ǰһԪ�ص���һ���ӦԪ��
Node* SkipList::DeleteHorizontalEle(Node* horizontal_head_node, int ele)
{
	Node* h_node, *tnode;
	h_node = horizontal_head_node->next;
	tnode = horizontal_head_node;

	while (h_node != NULL)
	{
		if (h_node->data < ele)
		{
			h_node = h_node->next;
			tnode = tnode->next;
		}
		else if(h_node->data==ele)
		{
			tnode->next = h_node->next;
			delete h_node;
			break;
		}
		else
		{
			break;
		}
	}
	return tnode->below;

}

// ͨ�����ú���ɾ��Ԫ�غ����Ӷ�ɾ����������ĸ�Ԫ��
int SkipList::DeleteElement(int ele)
{
	Node *vertical_node;
	vertical_node = head->below;

	while (vertical_node != NULL)
	{
		vertical_node=DeleteHorizontalEle(vertical_node, ele);
		
	}

	return 0;
}

int SkipList::ClearHorizontalLineEle(Node * horizontal_head_node)
{
	Node *tnode;

	while (horizontal_head_node->next!=NULL)
	{
		tnode= horizontal_head_node->next;
		horizontal_head_node->next = tnode->next;
		delete tnode;
	}
	
	return 0;
}

//�ͷ�ȫ���ڵ�
int SkipList::ClearSkipList()
{
	Node *vertical_head_node;
	vertical_head_node = head->below;

	while (vertical_head_node != NULL)
	{
		ClearHorizontalLineEle(vertical_head_node);
		vertical_head_node = vertical_head_node->below;
	}
	delete head;
	return 0;
}
int main()
{
	SkipList lst;
	srand((unsigned)time(NULL));
	int array[] = { 1,2,3,4,5,7,8,6,9 };
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		lst.InsertSkipList(array[i]);
	}
	lst.ShowSkipList();

	cout << "  1.��ѯԪ��\n";
	cout << "  2.ɾ��Ԫ��\n";
	cout << "  3.����Ԫ��\n";
	cout << "  4.��ʾ����\n";
	cout << "  5.�˳�\n";
	

	while (true)
	{	int op;
        cout << "  ��ѡ��\n";
		cin >> op;

		switch (op)
		{
		case 1:
		{
			float ele;
			cout << "������Ҫ��ѯ��Ԫ�أ�\n";
			scanf("%f", &ele);
			lst.SeekElement(ele);
			break;
		}
		case 2:
		{
			int ele;
			cout << "������Ҫɾ����Ԫ�أ� \n";
			cin >> ele;
			lst.DeleteElement(ele);
			break;
		}
		case 3:
		{
			int ele;
			cout << "������Ҫ�����Ԫ�أ� \n";
			cin >> ele;
			lst.InsertSkipList(ele);
			break;
		}
		case 4:
		{
			lst.ShowSkipList();
			break;
		}
		default:
			exit(0);
		}
	}
	return 0;

}
