#include <stdio.h>
#include <conio.h>

int arr[100];
int count;

void main()
{
	int  i, j,t;

	printf("����������Ԫ�صĸ���1~100��"); 
	do
		scanf("%d", &count);
	while (count < =1);

	printf("�밴˳����������Ԫ�أ�");
	for (i = 0; i < count; i++)
		scanf("%d", &arr[i]);
	getchar();
	for (i = 0; i < count; i++)
		for (j = 0; j < count - i -1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				t = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = t;
			}
		}
	printf("����������Ϊ��");
	for (i = 0; i < count; i++)
		printf("%d\t", arr[i]); 
	
	getchar();
}
