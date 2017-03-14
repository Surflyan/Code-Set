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
//通过调用RandomLevel生成待插入元素
//若level大于当前跳表层数，则增加层数
//返回带插入元素层数
int SkipList::InitialSkipList()
{
	int l_level, t_level;
	Node *pnode = head;
	l_level = RandomLevel();
	t_level = l_level;
	while (t_level >=head->level)            //更新表头
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
		head->level = l_level + 1;      //更新表头head 层数
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

// 参数：待插入元素，插入层表头
// 按照从小到大，插入元素
// 返回插入节点指针
Node* SkipList::HorizontalInsert(Node *vNode, int ele)
{
	Node*pNode, *tNode, *rNode;
	pNode = vNode;
	tNode = vNode->next;

	while (tNode != NULL)
	{                                           //搜索插入位置
		if (tNode->data < ele)
		{
			pNode = pNode->next;
			tNode = tNode->next;
		}
		else
			break;
	}


	rNode = NewNode();
	rNode->data = ele;                           //插入结点
	rNode->next = pNode->next;
	rNode->level = pNode->level;
    pNode->next = rNode;

	return rNode;
}

// 参数： 带插入元素
// 调用初始化函数，返回此元素所在层数
// 从上往下，一次插入每层；

bool SkipList::InsertSkipList(int ele)
{
	int level;
	level = InitialSkipList();                 // 确定元素所在层数
	Node * tNode, *rNode, *pNode ;
	tNode = head;
	while (tNode->level > level)
	{
		tNode = tNode->below;                 //从表头向下找到开始插入的层
	}

	rNode = NULL;
	while (true)
	{
		pNode = HorizontalInsert(tNode, ele);    //依次插入每层
		if (rNode != NULL)
			rNode->below = pNode;            //将上层此元素指向下一层
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

//显示跳表
int SkipList::ShowSkipList()
{
	Node * pnode, *tnode;
	pnode = head;
	while (pnode->below != NULL)
	{   
		pnode = pnode->below;
	    
		cout << "第 " << pnode->level << " 层:";
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

//参数：横向搜索的表头结点或者相同元素的下层元素， 搜索元素值
//横向搜索，并返回最后搜索元素的下一层
//输出搜索过程所比较的元素，不输出右侧比较元素
Node * SkipList::SeekHorizontalEle(Node* vertical_node,int ele)
{
	Node*horizontal_node, *tnode;
	horizontal_node = vertical_node->next;
	tnode = vertical_node;
	if (horizontal_node == NULL || tnode->data==ele)            //若当前搜索结点下一个节点为空
	{                                                           //或者当前搜索节点值与搜索值相等，则直接输出当前节点值
		cout << "\n第 " << tnode->level << " 层：" << tnode->data;
		return tnode->below;
	}

	while (horizontal_node != NULL)             //横向搜索
	{
		if (horizontal_node->data > ele)
			break;
		cout << "\n第 " << horizontal_node->level << " 层： ";
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

//搜索元素，竖向搜索
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

//参数： 删除搜索起始结点，待删除元素值
//横向查找待删除元素，并删除
//返回已删除元素前一元素的下一层对应元素
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

// 通过调用横向删除元素函数从而删除整个跳表的该元素
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

//释放全部节点
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

	cout << "  1.查询元素\n";
	cout << "  2.删除元素\n";
	cout << "  3.插入元素\n";
	cout << "  4.显示跳表\n";
	cout << "  5.退出\n";
	

	while (true)
	{	int op;
        cout << "  请选择：\n";
		cin >> op;

		switch (op)
		{
		case 1:
		{
			float ele;
			cout << "请输入要查询的元素：\n";
			scanf("%f", &ele);
			lst.SeekElement(ele);
			break;
		}
		case 2:
		{
			int ele;
			cout << "请输入要删除的元素： \n";
			cin >> ele;
			lst.DeleteElement(ele);
			break;
		}
		case 3:
		{
			int ele;
			cout << "请输入要插入的元素： \n";
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
