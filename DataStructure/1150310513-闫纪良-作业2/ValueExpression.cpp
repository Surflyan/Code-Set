#include <stdio.h>
#include <iostream>
#include <math.h>
#define MaxElements (30)

using namespace std;

int NUM=0;
struct StackRecord;
typedef struct StackRecord *Stack;
StackRecord* CreateStack();
int IsEmpty(Stack S);
int IsFull(Stack S);
void MakeEmpty(Stack S);
void PushStack(char x, Stack S);
char PopStack(Stack S);
int DestroyStack(Stack S);
int Calu(int a, int b, char c);
struct StackRecord
{
	int Capacity;
	int TopOfStack;
	char *Array;
};

typedef struct StackRecord *Stack;


StackRecord* CreateStack()    //Stack CreateStack()
{
	Stack S;
	S = new StackRecord;
	S->Array = new char[MaxElements];
	S->Capacity = MaxElements;
	S->TopOfStack = -1;
	return S;
}

int IsEmpty(Stack S)
{
	return S->TopOfStack == -1;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity;
}

void MakeEmpty(Stack S)
{
	S->TopOfStack = -1;
}

void PushStack(char x, Stack S)
{
	if (IsFull(S))
		printf("Full Stack \n");
	else
		S->Array[++S->TopOfStack] = x;
}

char PopStack(Stack S)	
{
	char x;
	if (!IsEmpty(S))
	{
		x = S->Array[S->TopOfStack];
		S->TopOfStack--;
		return x;
	}
	else
	{
		printf("Empty Stack \n");
		return '0';
	}
}
int DestroyStack(Stack S)
{
	delete[]S->Array;
	delete S;
	return 1;
}


int DefPriority(char c)
{   
	int a=0;
	switch (c)
	{
	case '+':
	case'-':
		a = 1;
		break;
	case '*':
	case '/':
		a= 2;
		break;
	case '^':
		a = 3;
		break;
	case '#':
		a = -1;
		break;
	default:
		a = 0;
	}
	return a;
}

void TranPostfix(char M[], char P[])
{
	int i = 0, j = 0;
	Stack T = CreateStack();
	P[j++] = M[i++];
	while (P[j]!='#')
	{   
		if ('0' < M[i] && M[i]< '9')
			P[j++] = M[i++];
		else
		{

			if (M[i] == '(')
			{
				PushStack(M[i], T);
				i++;
				continue;
			}
			if (M[i] == ')')
			{

				while ((T->Array[T->TopOfStack]) != '(')
				{
					P[j++] = PopStack(T);
				}
				PopStack(T);
				i++;
				while(DefPriority(M[i]) <= DefPriority(T->Array[T->TopOfStack]))
				{   
					if (!IsEmpty(T))
						P[j++] = PopStack(T);
					else
						break;
					
				}
				PushStack(M[i], T);
				i++;
			}

			else
			{
				while (DefPriority(M[i]) <= DefPriority(T->Array[T->TopOfStack]))
				{  
					if (!IsEmpty(T))
						P[j++] = PopStack(T);
					else
						break;
				}

				PushStack(M[i], T);
				i++;
			}

		}
			if (T->Array[T->TopOfStack] == '#')
			{
				PopStack(T);
				while (!IsEmpty(T))
				{
					P[j++] = PopStack(T);
				}
				P[j] = '#';
			}
	}
	DestroyStack(T);
}

int CalExpression(char P[])
{
	int i=1;
	int a, b;
	Stack T=CreateStack();
	while (P[i]!='#')
	{
		if ('0' < P[i] && P[i] < '9')
		{
			PushStack(P[i], T);
			
		}
		else
		{   
			b = PopStack(T)-'0';
			a = PopStack(T)- '0';
			PushStack(Calu(a, b, P[i])+'0',T);
		}
        i++;
	}
	a = T->Array[0] - '0';
	DestroyStack(T);
	return a;
}

int Calu(int a, int b,char c)
{   
	int r;
	switch (c)
	{
	case '-':
		r= a - b;
		break;
	case '+':
		r = a + b; break;
	case '*':
		r = a*b; break;
	case '/':
		r = a / b; break;
	case '^':
		r = pow(a, b); break;

	}
	return r;
}

bool ReadText(char *M)
{
	FILE *fp;
	if ((fp = fopen("in.txt", "r")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(0);
	}
	int i=0;
	int elm;
	while (!feof(fp))
	{
		
		if (i < MaxElements)
		{
			/*if (fscanf(fp, "+%d", &elm))
			{
			   M[i] = elm+'0';
			}
			else*/
			M[i] = fgetc(fp);
			i++;
		}
		else
			printf("Array Full\n");
	}
	
}


bool WriteText(char *p)
{
	FILE *fp;
	if ((fp = fopen("in.txt", "a")) == NULL)
	{
		cerr << "The file can not be open " << endl;
		exit(0);
	}
	int flag = 0;
	int i = 0;
	fputc('\n', fp);
	while (flag < 2)
	{
		if (p[i] == '#')
			flag++;

		fputc(p[i],fp);
		i++;
	}
}
int main()
{
	char M[MaxElements] = { '$' };
	char P[MaxElements] = { '$' };
	int a;
	ReadText(M);
	TranPostfix(M, P);
	WriteText(P);
	a = CalExpression(P);
	printf("%d", a);
}