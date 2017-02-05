#include<iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>

//汇编中的东东
extern "C" int N;
extern "C" int qi(char *buf, int *pi, char chr);
extern "C" int qo(char *buf, int*po, char *chr);
extern "C" int qp(char *buf, int pi, int po);

extern "C"
{
	void incp(int *p);
}

char buf[16];
int pi = 0;
int po = 0;
char chr;

void incp(int *p);
int main() 
{
	int a;
	char chr;
	printf("请选择：ESC 退出； - 从队列提取元素显示 + 打印当前队列；0 - 9A - Z进入队列，其他抛弃。\n");
	while (true)
	{
		chr = _getche();
		if (chr == 0X1B)
			break;
		if (chr == '+')
		{
			qp(buf, pi, po);
		}
		if (chr == '-')
		{
			a = qo(buf, &po, &chr);
			if (a == 1)
				printf("提取的元素为%c\n", chr);
			else
				printf("NONE\n");
		}
		else if ((chr >= '0'&&chr <= '9') || (chr >= 'A'&&chr <= 'Z'))
		{
			a = qi(buf, &pi, chr);
			if (a == 0)
				printf("\nFULL\n");
		}
	}
	return 0;
}

//求模
void incp(int* p)
{  
	*p=*p+1;
	*p = *p % 16;
}