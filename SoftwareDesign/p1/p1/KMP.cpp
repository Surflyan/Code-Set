#include <iostream>
#include <string>
#include <stdio.h>

#define LEN 100     //字符串最大长度

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
	char main_str[LEN];      //文本串
	char pattern_str[LEN];      //模式串
	int next[LEN];

    printf("请输入文本串：\n");
	gets_s(main_str);
	printf("请输入模式串：\n");
	
	gets_s(pattern_str);
    
	GetNext(pattern_str, next);
	int res = KMPmatch(main_str, pattern_str, next);

	if (res == -1)
		printf("当前主串中不含有模式串！\n ");
	else
		printf("模式串出现在主串的%d 号下标处\n", res);

    
}
