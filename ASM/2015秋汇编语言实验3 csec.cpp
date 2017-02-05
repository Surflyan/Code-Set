// csec.cpp : �������̨Ӧ�ó������ڵ㡣
//

#define _CRT_SECURE_NO_WARNINGS
#include "string.h" 
#include "stdio.h"

void swap(unsigned char *c1, unsigned char *c2)
{
	char t;
	t = (*c1);
	(*c1) = (*c2);
	(*c2) = t;
}

void updown(unsigned char *buf, int len)
{
	int i;

	for (i = 0; i < len / 2; i++)
	{
		swap(&(buf[i]), &(buf[len - i - 1]));
	}
}

void lshift(unsigned char *buf, int len)
{
	int newhbit, oldhbit;

	oldhbit = buf[0] / 0x80;
	for (int i = len - 1; i >= 0; i--)
	{
		newhbit = buf[i] / 0x80;
		buf[i] <<= 1;
		buf[i] ^= oldhbit;
		oldhbit = newhbit;
	}
}

void GenCRC(unsigned char *data, unsigned char *crc, int len)
{
	int bitlen, hbit;
	unsigned char buf[100];

	memcpy(buf, data, len);	buf[len] = buf[len + 1] = 0;	len += 2;
	for (bitlen = len * 8; bitlen > 16; bitlen--)
	{
		hbit = buf[0] & 0x80;
		lshift(buf, len);
		if (hbit)
		{
			buf[0] ^= 0x80;	buf[1] ^= 0x05;
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
	GenCRC(buf, t, l);

	for (i = 0; i < 2; i++)
	{
		sprintf((char *)(pass + i * 2), "%02X", (unsigned char)(t[i]));
	}
}

void main()
{
	int i;
	unsigned char yname[100];
	unsigned char pass1[100];
	unsigned char pass2[200];

	printf("�������������: ");
	scanf("%s", &yname);
	printf("====��ʼ��������====\n");
	makepass(yname, pass2);
	printf("====�����������====\n");

rpl:printf("�������������: ");
	scanf("%s", &pass1);
	printf("====��ʼ�Ƚ�����====\n");
	if (strcmp((char*)pass1, (char*)pass2) == 0)
	{
		printf("====��ӭ�������ǵ���Ϣϵͳ���й������ ====\n");
	}
	else
	{
		printf("====�������====\n");
		goto rpl;
	}

	return;
}