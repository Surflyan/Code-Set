// csec.cpp : 定义控制台应用程序的入口点。
//

#define _CRT_SECURE_NO_WARNINGS
#include "string.h" 
#include "stdio.h"

//交换两字符 
void swap(unsigned char *c1, unsigned char *c2)
{
	char t;
	t = (*c1);
	(*c1) = (*c2);
	(*c2) = t;
}

//字符串逆置 
void updown(unsigned char *buf, int len)
{
	int i;

	for (i = 0; i < len / 2; i++)
	{
		swap(&(buf[i]), &(buf[len - i - 1]));
	}
}

//将整个字符串当作一个长二进制串 ，循环左移一位 
void lshift(unsigned char *buf, int len)
{
	int newhbit, oldhbit;

	oldhbit = buf[0] / 0x80; 	//oldhbit等于buf[0]的最高位 
	for (int i = len - 1; i >= 0; i--)	//从最后一个字符往回处理 
	{
		newhbit = buf[i] / 0x80;	//将当前字符最高位保存到newhbit中  
		buf[i] <<= 1; 	//当前字符二进制串左移一位 
		buf[i] ^= oldhbit;	//将上一个字符的最高位赋给当前字符二进制串的最低位 ，等价于buf[i] |= oldhbit; 
		oldhbit = newhbit; 
	}
}

//生成CRC码。在原有的字符串后增加两字节空间， 使得最高两字节能容纳 CRC码。 
void GenCRC(unsigned char *data, unsigned char *crc, int len)
{
	int bitlen, hbit;
	unsigned char buf[100];

	memcpy(buf, data, len);	buf[len] = buf[len + 1] = 0;	len += 2;
	for (bitlen = len * 8; bitlen > 16; bitlen--)
	{
		hbit = buf[0] & 0x80;	//将第一字节除最高位外每一位都和1相与 
		lshift(buf, len);	//整个字符二进制串循环左移一位 
		if (hbit)
		{
			buf[0] ^= 0x80;	buf[1] ^= 0x05;	//如果最高位是1，则第一字节与128异或，第二字节与5异或 
		}
		//	 LShift(buf,len);
	}
	memcpy(crc, buf, 2);
}


void makepass(unsigned char *buf, unsigned char *pass)
{
	int i;
	int l;
	unsigned char t[10];

	l = strlen((char*)buf);
	updown(buf, l);
	GenCRC(buf, t, l);	//t存放crc码 

	for (i = 0; i < 2; i++)
	{
		sprintf((char *)(pass + i * 2), "%02X", (unsigned char)(t[i]));	//以十六进制数输出两字节CRC码 作为用户密码 
	}
}

void main()
{
	int i;
	unsigned char yname[100];
	unsigned char pass1[100];
	unsigned char pass2[200];

	printf("请输入你的姓名: ");
	scanf("%s", &yname);
	printf("====开始生成密码====\n");
	makepass(yname, pass2);
	printf("====生成密码结束====\n");

rpl:printf("请输入你的密码: ");
	scanf("%s", &pass1);
	printf("====开始比较密码====\n");
	if (strcmp((char*)pass1, (char*)pass2) == 0)
	{
		printf("====欢迎进入我们的信息系统进行管理操作 ====\n");
	}
	else
	{
		printf("====密码错误====\n");
		goto rpl;
	}

	return;
}
