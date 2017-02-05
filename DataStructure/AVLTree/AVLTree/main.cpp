#include <iostream>
#include "AVL.h"

#define N  30             //最大序列个数
using namespace std;

//读取文件，将序列读取到sequence数组中
void ReadText(int sequence[])
{
	FILE * fp;
	if ((fp = fopen("AVL.txt", "r")) == NULL)
	{
		cerr << "The File Can not be open ！" << endl;
		exit(0);
	}
	int key;
	int i = 0;
	while (fscanf(fp,"%d",&key))
	{
		sequence[i] = key;
		i++;
	}
	sequence[i] = -1;
	fclose(fp);

}
int main()
{
	int sequence[N];
	ReadText(sequence);
	Node *root=NULL ;

	//根据sequence序列，建立AVL树，并纵向打印树以显示变化
	{
		int length;
		int i = 0;
		while (sequence[i++] != -1)
			length = i;
		for (i = 0; i < length; i++)
		{
			cout << "插入" << sequence[i] << ":" << endl;
			root = InsertNode(root, sequence[i]);
			TreePrint(root, 0);
			cout << "_________________________" << endl;
		}
		    
	}

	cout << "	请选择：" << endl;
	cout << "	1.查找" << endl;
	cout << "	2.删除" << endl;
	cout << "	3.插入" << endl;
	cout << "	4.排序" << endl;
	cout << "	5.退出" << endl;
	while (true)
	{  
		cout << "	请选择：" << endl;
		int op;
		cin >> op;
		if (op == 1)
		{   
			cout << "待查找元素：";
			int element;
			cin >> element;
			Node *text;
			text = SearchNode(root, element);
			cout << text->data << endl;
		}
		else if (op == 2)
		{
			cout << "待删除元素：";
			int element;
			cin >> element;
			DeleteNode(root, element);
			TreePrint(root, 0);
		}
		else if (op == 3)
		{
			cout << "待插入元素：";
			int element;
			cin >> element;
			InsertNode(root, element);
			TreePrint(root, 0);
		}
		else if (op == 4)
		{
			InOrderSort(root);
			cout << endl;
		}

		else
			break;
	}
	DestroyTree(root);
	return 0;
}