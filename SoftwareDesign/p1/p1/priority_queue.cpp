#include <iostream>
#include <stdio.h>
#define MAXNUM 15
#define T int

using namespace std;

struct Node
{
	T data;
	int priority;
	Node * next;

};
class PriorQueue
{
public:
	PriorQueue()
	{
		head = new Node;
		head->priority = 0;
		head->next = NULL;
	}

	bool Insert(T ele, int pri);
	void ShowQueue();
	T Pop();
	T Top();
	int  CheckHighSeriesElement();
	bool ClearPriorQueue();
	bool InsertSeriesElement(T ele_array[],int pri_array[],int num_ele );
	bool ChangeElementPriority(T ele, int pri);
	bool UnitePriorityQueue(PriorQueue second_queue);
	
	int CalAllNumber();
private:
   Node *head;

 };

bool PriorQueue::Insert(T ele, int pri)
{
	Node * new_node;
	Node *pnode, *tnode;
	new_node = new Node;
	pnode = head->next;
	tnode = head;
	while (pnode !=NULL)
	{
		if (pnode->priority > pri)
		{
			pnode = pnode->next;
			tnode = tnode->next;
		}
		else
			break;
	}

	new_node->data = ele;
	new_node->priority = pri;
	new_node->next = tnode->next;
	tnode->next = new_node;

	return true;
  
}


void PriorQueue::ShowQueue()
{
	Node *pnode = head->next;
	while (NULL != pnode)
	{
		cout << pnode->data << " ";
		pnode = pnode->next;
	}
	cout << endl;
}


T PriorQueue::Pop()
{
	Node *pnode = head->next;
	T d;
	if (pnode!= NULL)
	{
		head->next = pnode->next;
		d = pnode->data;
	    delete pnode;
		return d;
	}

	return -1;

}



T PriorQueue::Top()
{
	Node *pnode = head->next;
	T d;
	if (pnode->next != NULL)
	{
		d = pnode->data;
		return d;
	}

	return -1;
}


int PriorQueue::CheckHighSeriesElement()
{
	Node *pnode = head->next;
	int num_high_element = 0;

	
	while (NULL != pnode)
	{   
		if (pnode->priority == head->next->priority)
		{
			cout<<pnode->data<< " ";
			pnode = pnode->next;
			num_high_element++;
		}
		else
			break;
	}
	return num_high_element;
}


bool PriorQueue::ClearPriorQueue()
{
	Node *pnode;
	while (NULL != head->next)
	{
		pnode = head->next;
		head->next = pnode->next;
		delete pnode;
	}
	return true;

}



bool PriorQueue::ChangeElementPriority(T ele, int pri)
{
	Node *tnode = head;
	Node *pnode = head->next;
	while (NULL != pnode)
	{
		if (pnode->data == ele)
		{
			tnode->next = pnode->next;
			break;
		}
		else
		{
			tnode = tnode->next;
			pnode = pnode->next;
		}

	}

	Insert(ele, pri);

	return true;
}


bool PriorQueue::InsertSeriesElement(T ele_array[], int pri_array[],int num_ele)
{   
	int i = 0;
	while (i<num_ele)
	{
		this->Insert(ele_array[i], pri_array[i]);
		i++;
	}
	return true;
}


bool PriorQueue::UnitePriorityQueue(PriorQueue second_queue)
{
	Node*pnode = second_queue.head->next;
	while (NULL != pnode)
	{
		this->Insert(pnode->data, pnode->priority);
	}
	second_queue.ClearPriorQueue();
	
	return true;
}

int PriorQueue::CalAllNumber()
{
	int res=0;
	int x, y;
	while (head->next != NULL)
	{
		x = this->Pop();
		y = this->Pop();
		res += x + y;
		this->Insert(x + y, -x - y);
	}

	return res;

}

int main()
{   
	PriorQueue Q;
	int num_ele;
    cout << "			hello!\n";
	cout << "		1.单独插入元素 \n";
	cout << "		2.取出最高优先级元素 \n";
	cout << "		3.查看最高优先级的元素 \n";
	cout << "		4. 查看优先级最高的批元素\n";
	cout << "		5.清空优先队列\n";
	cout << "		6.批插入元素 \n";
	cout << "		7.合并优先队列\n";
	cout << "		8.调整一个元素的优先级\n";
	cout << "		9.显示优先队列\n";
	cout << "		10. 退出 \n";

	while (true)
	{
		int op;
		cout << "		 请选择：\n";
		cin >> op;

		switch (op)
		{
		case 1:
		{
			int ele;
			cout << "请输入元素：\n";
			cin >> ele;
			Q.Insert(ele, -ele);
			break;
		}
		case 2:
		{
			cout << Q.Pop();
			break;
		}
		case 3:
		{
			cout << Q.Top();
			break;
		}
		case 4:
		{
			Q.CheckHighSeriesElement();
			break;
		}
		case 5:
		{
			Q.ClearPriorQueue();
			break;
		}
		case 6:
		{
			printf("请输入元素个数：\n");
			scanf("%d", &num_ele);

			int * queue_array = new int[num_ele];
			int * priority_array = new int[num_ele];

			printf("请输入待排列元素：\n");

			int i;
			for (i = 0; i < num_ele; i++)
			{
				scanf("%d", &queue_array[i]);
				priority_array[i] = -queue_array[i];
			}


			Q.InsertSeriesElement(queue_array, priority_array, num_ele);
			break;
		}
		case 7:
		{

			PriorQueue N;
			Q.UnitePriorityQueue(N);
			break;
		}
		case 8:
		{
			int ele, pri;
			cout << "请输入调整的元素与优先级：\n";
			cin >> ele >> pri;
			Q.ChangeElementPriority(ele, pri);
			break;
		}
		case 9:
		{
			Q.ShowQueue();
			break;
		}

		default:
			exit(0);

		}
		
	}

	return 0;
}