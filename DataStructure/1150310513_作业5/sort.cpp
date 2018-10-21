#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "mytime.h"

#define NumDigit 10

using namespace std;
//生成NumDigit个随机数;
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

//交换两元素，改变实参
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

//分区的实现，
int Partition(int pSeq[], int left, int right)
{
	int pivotValue = pSeq[right];                 //选取最后一个元素为基准元素
	int storeIndex = left;

	for (int i = left; i < right; i++)            //比基准元素小的放左边
	{
		if (pSeq[i] < pivotValue)
		{
			Swap(pSeq[storeIndex], pSeq[i]);
			storeIndex++;
		}
	}
	Swap(pSeq[right], pSeq[storeIndex]);           //基准元素的位置
	return storeIndex;
}

/*递归快速排序
参数：待排序列 0 元素个数-1
*/

int QuickSort(int pSeq[], int left, int right)
{
	if (left > right) return 0;
	int storeIndex = Partition(pSeq, left, right);
	QuickSort(pSeq, left, storeIndex - 1);
	QuickSort(pSeq, storeIndex + 1, right);

	return 1;
}

//直接插入排序
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

//直接选择排序
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
调整以index下标为根结点的子堆的最大化
Parent(i) = floor((i-1)/2)，i 的父节点下标
Left(i) = 2i + 1，i 的左子节点下标
Right(i) = 2(i + 1)，i 的右子节点下标
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
		else                                        //出口：此结点key大于孩子结点的key
			break;                                  //中间有一个结点不需调整，后序也已排好

	}
}

/*建立最大堆*/
void BuildMaxHeap(int pSeq[], int headSize)
{
	int i;
	for (i = (headSize - 1) / 2; i >= 0; i--)      //从n/2结点开始上溯
		PushDown(pSeq, i, headSize);
}
/*最大堆排序，升序排序*/
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
//打印序列
void PrintSeq(int Seq[], int pNum)
{
	for (int i = 0; i < pNum; i++)
	{
		printf("%d ", Seq[i]);
	}
}

//非递归二分查找，找到返回下标，未找到返回-1；
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
	return -1;                            //未找到
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
	cout << "生成的随机序列： " << endl;
	PrintSeq(Seq, NumDigit);
	stop_watch timer;

	CreatRandomDigit(Seq, NumDigit);
	cout << endl << "冒泡排序： " << endl;
	
	timer.restart();
	BubbleSort(Seq, NumDigit);
	timer.stop();
	timeuse = timer.elapsed();
    PrintSeq(Seq, NumDigit);

	CreatRandomDigit(Seq, NumDigit);
	cout << endl << "快速排序： " << endl;
	timer.restart();
	QuickSort(Seq, 0, NumDigit - 1);
	timer.stop();
	timeuse2 = timer.elapsed();
	PrintSeq(Seq, NumDigit);


	printf("\n冒泡排序时间：%lf\n", timeuse);
	printf("快速排序时间：%lf\n", timeuse2);
	cout << endl << "输入查找元素：" << endl;
	int a;
	cin >> a;
	cout << "非递归查找：";
	timer.restart();
	cout << BinSearch(Seq, NumDigit, a);
	timer.stop();
	cout << "非递归查找时间："<<timer.elapsed() << endl;

	cout << endl << "递归查找：";
	
	cout << RecursiveBinSearch(Seq, 0, NumDigit, a);
	
	getchar();
	getchar();

	return 0;
}
