#include<iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>

//����еĶ���
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
	printf("��ѡ��ESC �˳��� - �Ӷ�����ȡԪ����ʾ + ��ӡ��ǰ���У�0 - 9A - Z������У�����������\n");
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
				printf("��ȡ��Ԫ��Ϊ%c\n", chr);
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

//��ģ
void incp(int* p)
{  
	*p=*p+1;
	*p = *p % 16;
}