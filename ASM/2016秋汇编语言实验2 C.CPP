#include <stdio.h>
#include <conio.h>
#include <string.h>


extern "C" int n;
extern "C" int iq(char *buf,int *ip,char chr);
extern "C" int oq(char *buf,int *op,char *chr);
extern "C" int pq(char *buf, int ip, int op);


extern  "C"
{
	void incp(int *pp);
}

char buf[16];
int  ip = 0,op = 0;
int  chr;

int main()
{
	char chr;
	unsigned int  m = 0;

	printf("请选择：ESC 退出； - 从队列提取元素显示 + 打印当前队列；0 - 9A - Z进入队列，其他抛弃。\n");

	for (;;)
	{
		chr = _getche();
		if (chr == 0x1B) 
			break;
		else if (chr == '-')
		{
			m = oq(buf,&op,&chr);
-			if (m != 0)
				printf("	提取的元素为：%c \n", chr);
			else
				printf("	EMPTY!\n");
		}
		else if (chr == '+')
		{
			m = pq(buf, ip, op);
		}
		else if (chr >= '0' && chr <= '9' || chr >= 'A' && chr <= 'Z')
		{
			m = iq(buf,&ip,chr);
			if (m == 0) 
				printf("	FULL!\n");
		}
		//printf("\n当前元素个数%2d\n", n);
	}
	system("pause");
	return    0;
}