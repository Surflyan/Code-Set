#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "mytime.h"

#define NumDigit 10

using namespace std;
//����NumDigit�������;
int CreatRandomDigit(int pSeq[], int pNum)
{
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < pNum; i++)
	{
		pSeq[i] = rand();
	}
	return 0;
}

//������Ԫ�أ��ı�ʵ��
void Swap(int& a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int BubbleSort(int Seq[], int pNum)
{
	int i, j;
	for (i = 0; i < pNum; i++)
	{
		for (j = i + 1; j < pNum; j++)
		{
			if (Seq[i] > Seq[j])
				Swap(Seq[i], Seq[j]);
		}
	}
	return 0;
}

//������ʵ�֣�
int Partition(int pSeq[], int left, int right)
{
	int pivotValue = pSeq[right];                 //ѡȡ���һ��Ԫ��Ϊ��׼Ԫ��
	int storeIndex = left;

	for (int i = left; i < right; i++)            //�Ȼ�׼Ԫ��С�ķ����
	{
		if (pSeq[i] < pivotValue)
		{
			Swap(pSeq[storeIndex], pSeq[i]);
			storeIndex++;
		}
	}
	Swap(pSeq[right], pSeq[storeIndex]);           //��׼Ԫ�ص�λ��
	return storeIndex;
}

/*�ݹ��������
�������������� 0 Ԫ�ظ���-1
*/

int QuickSort(int pSeq[], int left, int right)
{
	if (left > right) return 0;
	int storeIndex = Partition(pSeq, left, right);
	QuickSort(pSeq, left, storeIndex - 1);
	QuickSort(pSeq, storeIndex + 1, right);

	return 1;
}

//ֱ�Ӳ�������
int InsertSort(int pSeq[], int pNum)
{
	int temp;
	for (int i = 1; i < pNum; i++)
	{
		temp = pSeq[i];
		for (int j = i; j >= 0; j--)
		{
			if (pSeq[j - 1] > temp)
				pSeq[j] = pSeq[j - 1];
			else
			{
				pSeq[j] = temp;
				break;
			}
		}
	}

	return 0;
}

//ֱ��ѡ������
int SelectSort(int pSeq[], int pNum)
{
	int i, j, lowIndex;
	for (i = 0; i < pNum; i++)
	{
		lowIndex = i;
		for (j = i + 1; j < pNum; j++)
		{
			if (pSeq[j] < pSeq[lowIndex])
				lowIndex = j;
		}
		if (lowIndex != i)
			Swap(pSeq[i], pSeq[lowIndex]);
	}

	return 0;
}
/*
������index�±�Ϊ�������Ӷѵ����
Parent(i) = floor((i-1)/2)��i �ĸ��ڵ��±�
Left(i) = 2i + 1��i �����ӽڵ��±�
Right(i) = 2(i + 1)��i �����ӽڵ��±�
*/
void PushDown(int pSeq[], int index, int heapSize)
{
	int iMax;
	int left, right;
	while (true)
	{
		iMax = index;
		left = 2 * index + 1;
		right = 2 * (index + 1);

		if (left < heapSize && pSeq[index] < pSeq[left])
			iMax = left;
		if (right < heapSize && pSeq[iMax] < pSeq[right])
			iMax = right;
		if (iMax != index)
		{
			Swap(pSeq[iMax], pSeq[index]);
			index = iMax;
		}
		else                                        //���ڣ��˽��key���ں��ӽ���key
			break;                                  //�м���һ����㲻�����������Ҳ���ź�

	}
}

/*��������*/
void BuildMaxHeap(int pSeq[], int headSize)
{
	int i;
	for (i = (headSize - 1) / 2; i >= 0; i--)      //��n/2��㿪ʼ����
		PushDown(pSeq, i, headSize);
}
/*����������������*/
int HeapSort(int pSeq[], int headSize)
{
	BuildMaxHeap(pSeq, headSize);
	for (int i = headSize - 1; i > 0; i--)
	{
		Swap(pSeq[i], pSeq[0]);
		PushDown(pSeq, 0, i);
	}
	return 0;
}
//��ӡ����
void PrintSeq(int Seq[], int pNum)
{
	for (int i = 0; i < pNum; i++)
	{
		printf("%d ", Seq[i]);
	}
}

//�ǵݹ���ֲ��ң��ҵ������±꣬δ�ҵ�����-1��
int BinSearch(int pSeq[], int pNum, int key)
{
	int low, high, mid;
	low = 0;
	high = pNum;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (pSeq[mid] == key)
			return mid;
		else if (pSeq[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;                            //δ�ҵ�
}

int RecursiveBinSearch(int pSeq[], int low, int high, int key)
{
	if (low > high)
		return -1;
	int mid = (low + high) / 2;
	if (pSeq[mid] == key)
		return mid;
	else if (pSeq[mid] < key)
		return RecursiveBinSearch(pSeq, mid + 1, high, key);
	else
		return RecursiveBinSearch(pSeq, low, mid - 1, key);
}
int main()
{

	double timeuse, timeuse2;
	int *Seq = new int[NumDigit];
	CreatRandomDigit(Seq, NumDigit);
	cout << "���ɵ�������У� " << endl;
	PrintSeq(Seq, NumDigit);
	stop_watch timer;

	CreatRandomDigit(Seq, NumDigit);
	cout << endl << "ð������ " << endl;
	
	timer.restart();
	BubbleSort(Seq, NumDigit);
	timer.stop();
	timeuse = timer.elapsed();
    PrintSeq(Seq, NumDigit);

	CreatRandomDigit(Seq, NumDigit);
	cout << endl << "�������� " << endl;
	timer.restart();
	QuickSort(Seq, 0, NumDigit - 1);
	timer.stop();
	timeuse2 = timer.elapsed();
	PrintSeq(Seq, NumDigit);


	printf("\nð������ʱ�䣺%lf\n", timeuse);
	printf("��������ʱ�䣺%lf\n", timeuse2);
	cout << endl << "�������Ԫ�أ�" << endl;
	int a;
	cin >> a;
	cout << "�ǵݹ���ң�";
	timer.restart();
	cout << BinSearch(Seq, NumDigit, a);
	timer.stop();
	cout << "�ǵݹ����ʱ�䣺"<<timer.elapsed() << endl;

	cout << endl << "�ݹ���ң�";
	
	cout << RecursiveBinSearch(Seq, 0, NumDigit, a);
	
	getchar();
	getchar();

	return 0;
}
