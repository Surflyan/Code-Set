#include <iostream>
#include "AVL.h"

#define N  30             //������и���
using namespace std;

//��ȡ�ļ��������ж�ȡ��sequence������
void ReadText(int sequence[])
{
	FILE * fp;
	if ((fp = fopen("AVL.txt", "r")) == NULL)
	{
		cerr << "The File Can not be open ��" << endl;
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

	//����sequence���У�����AVL�����������ӡ������ʾ�仯
	{
		int length;
		int i = 0;
		while (sequence[i++] != -1)
			length = i;
		for (i = 0; i < length; i++)
		{
			cout << "����" << sequence[i] << ":" << endl;
			root = InsertNode(root, sequence[i]);
			TreePrint(root, 0);
			cout << "_________________________" << endl;
		}
		    
	}

	cout << "	��ѡ��" << endl;
	cout << "	1.����" << endl;
	cout << "	2.ɾ��" << endl;
	cout << "	3.����" << endl;
	cout << "	4.����" << endl;
	cout << "	5.�˳�" << endl;
	while (true)
	{  
		cout << "	��ѡ��" << endl;
		int op;
		cin >> op;
		if (op == 1)
		{   
			cout << "������Ԫ�أ�";
			int element;
			cin >> element;
			Node *text;
			text = SearchNode(root, element);
			cout << text->data << endl;
		}
		else if (op == 2)
		{
			cout << "��ɾ��Ԫ�أ�";
			int element;
			cin >> element;
			DeleteNode(root, element);
			TreePrint(root, 0);
		}
		else if (op == 3)
		{
			cout << "������Ԫ�أ�";
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