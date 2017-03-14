#include <iostream>
#include <string>
#include <stdio.h>

#define LEN 100     //�ַ�����󳤶�

using namespace std;
void GetNext(char pattern_str[], int next[])
{
	int len = strlen(pattern_str);
	int i = -1, j = 0;

	next[0] = -1;
	while (j < len - 1)
	{
		if (i == -1 || pattern_str[j] == pattern_str[i])
		{
			++i;
			++j;
			next[j] = i;

		}
		else
			i= next[i];

	}

}


int KMPmatch(char main_str[],char pattern_str[],int next[])
{
	int i = 0, j = 0;
	
	int main_str_len = strlen(main_str);
	int pattern_str_len = strlen(pattern_str);

	while (i < main_str_len &&j < pattern_str_len)
	{
		if (j == -1 || main_str[i] == pattern_str[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == pattern_str_len)
		return i - j;
	else
		return -1;

}

int main()
{
	char main_str[LEN];      //�ı���
	char pattern_str[LEN];      //ģʽ��
	int next[LEN];

    printf("�������ı�����\n");
	gets_s(main_str);
	printf("������ģʽ����\n");
	
	gets_s(pattern_str);
    
	GetNext(pattern_str, next);
	int res = KMPmatch(main_str, pattern_str, next);

	if (res == -1)
		printf("��ǰ�����в�����ģʽ����\n ");
	else
		printf("ģʽ��������������%d ���±괦\n", res);

    
}
