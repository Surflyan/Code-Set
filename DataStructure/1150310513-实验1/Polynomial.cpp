//���ݽṹʵ��1������ʵ�ֶ���ʽ����������
//2016.10.30

#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

//����ʽ���
struct PolyNode
{  
	float coef;
	int  exp;
	PolyNode * next;
};

//����ʽ��
class PolyLink
{   
public:
	PolyLink() { head = new PolyNode;
	             head->next = NULL;              //��������ʽ
	            }
	~PolyLink() { ClearLink(); delete head; }    //��ն���ʽ

	void  SortLink();                            //��������
	float CalLink(float x);                      //������ֵ
	int   InsertNode(PolyNode& node);            // ���뺯��
	
	PolyLink & AddLink(PolyLink &L1);             //+
	PolyLink & SubLink(PolyLink &L);              //-
	PolyLink & MulLink(PolyLink &L);              //*
	PolyLink & DivLink(PolyLink &L,PolyLink &T);  // /
	void AddThisLink(PolyLink &L);                //����ʽ��ӵ�������
	void ShowLink();                             // ����̨���
	void ClearLink();                             //���


	PolyNode *head;                            //ͷ���
};


// ���������� ��ѡ������
// δ�����ڵ�λ�ã�ϵ������
void PolyLink::SortLink()
{
	PolyNode *pNode = head->next;
	float temp1;
	int temp2;
	while (pNode != NULL)
	{
		PolyNode *tNode = pNode->next;
		while (tNode != NULL)
		{
			if (pNode->exp < tNode->exp)       
			{   
				temp1= pNode->coef;
				temp2 = pNode->exp;            //ֱ�ӽ���ϵ�����ݴ�
				pNode->coef = tNode->coef;
				pNode->exp = tNode->exp;
				tNode->coef = temp1;
				tNode->exp = temp2;
			}
			tNode = tNode->next;
			
		}
		pNode = pNode->next;
	}
}

//������ֵ����
float PolyLink::CalLink(float x)
{
	float sum=0;
	PolyNode *pNode = head->next;
	while (pNode != NULL)
	{
		float a=pNode->coef;
		int b=pNode->exp;
		sum = sum + a* pow(x, b);      //������ֵ
		pNode = pNode->next;
	}
	return sum;
}

//���뺯��
//���ݴβ��뵽�����ڵ�λ�ã����ԭ���������и��ݴΣ�ϵ�����
int  PolyLink::InsertNode(PolyNode & node)
{
	PolyNode * pNode = new PolyNode;
	PolyNode *tNode = this->head;
	pNode->exp = node.exp;
	pNode->coef = node.coef;
	pNode->next = NULL;
	if (tNode->next == NULL)
	{                                     //�������Ϊ�գ����뵽��һλ
		tNode->next = pNode;
		return 1;                     
	}
	while (tNode->next != NULL)
	{
		if (tNode->next->exp < pNode->exp)
		{   
			pNode->next = tNode->next;
			tNode->next = pNode;	                 //�ҵ�λ�ò�����
			return 1;
		}
		if (tNode->next->exp == pNode->exp)
		{
			tNode->next->coef += pNode->coef;         //ͬ�ݴ�ֱ�����
			if (tNode->next->coef == 0)
			{   
				pNode = tNode->next;
				tNode->next = pNode->next;             //���Ϊ�㣬ɾ�����
				delete pNode;
			}
			return 1;
		}
		tNode = tNode->next;
	}
	tNode->next = pNode;
	return 1;
}

//����ʽ��ӣ������µ��������ı�ԭ��

PolyLink& PolyLink::AddLink(PolyLink &L1)
{
	PolyLink *resLink = new PolyLink;       //�洢�������ʽ
	PolyNode *pa = L1.head->next; 
	PolyNode *pb = this->head->next;
	while (pa != NULL &&pb != NULL)         //�������
	{   
		if (pa->exp > pb->exp)
		{   
			resLink->InsertNode(*pa);       //���ݴε��Ȳ���
			pa = pa->next;
		}
		else if (pa->exp==pb->exp)
		{   
			PolyNode *pNode = new PolyNode;         //ͬ�ݴ�ϵ�����
			pNode->coef = pa->coef + pb->coef;
			pNode->exp = pa->exp; 
			pNode->next = NULL;
			if (0 == pNode->coef)                //���ϵ��Ϊ�㣬�����
			{
                pa = pa->next;
			    pb = pb->next;
				delete pNode;
				continue;
			}			
			resLink->InsertNode(*pNode);          
			pa = pa->next;
			pb = pb->next;
			delete pNode;
		}
		else
		{
			resLink->InsertNode(*pb);
			pb = pb->next;
		}
	}
	while (pa != NULL)               //������������ӵ��������ʽ
	{
		resLink->InsertNode(*pa);
		pa = pa->next;	
	}
	while (pb != NULL)
	{
		resLink->InsertNode(*pb);
		pb= pb->next;
	}
	return *resLink;
}

//����ʽ����������µĶ���ʽ
PolyLink & PolyLink::SubLink(PolyLink &L)
{
	PolyLink *resLink = new PolyLink;            //��������ʽ
	PolyNode *pa = this->head->next;
	PolyNode *pb = L.head->next;

	while (pb != NULL)
	{
		pb->coef = -pb->coef;
		pb = pb->next;                      //��ԭ����ϵ��ȡ��
	}

	*resLink = this->AddLink(L);            //���üӷ�����

	pb = L.head->next;
	while (pb != NULL)
	{
		pb->coef = -pb->coef;               //��ԭ������ԭ
		pb = pb->next;
	}

	return *resLink;
}

//����ʽ��ˣ������¶���ʽ
//�ڶ����ÿһ��������ǰ����ˣ��ٲ���
PolyLink& PolyLink::MulLink(PolyLink &L)
{
	PolyLink *resLink = new PolyLink;         //��ṹ����ʽ
	PolyLink *pLink = new PolyLink;
	PolyNode *pNode = this->head->next;       
	PolyNode *tNode = L.head->next;
	PolyNode *rNode = new PolyNode;
	while (tNode != NULL)
	{   
		pNode = this->head->next;
		while (pNode != NULL)                //�ڶ�������ʽ�������һ�����
		{   
			rNode->coef = 0;             
			rNode->exp = 0;
			rNode->coef = tNode->coef*pNode->coef;
			rNode->exp = tNode->exp+pNode->exp;
			rNode->next = NULL;
			pLink->InsertNode(*rNode);         //��˽���ӵ��м�����
			pNode = pNode->next;
		}
	
		resLink->AddThisLink(*pLink);           //��ÿ�����ʽ�ӵ��������ʽ��
		pLink->ClearLink();                     //����м����ʽ
		tNode =tNode->next;

	}
	delete pLink;
	delete rNode;
	return *resLink;		
}

//����ʽ��ӣ����������������ص���ǰ����ʽ��
void PolyLink::AddThisLink(PolyLink&L)
{   
	PolyNode *pb = L.head->next;
	PolyNode *pa = this->head;
	PolyNode *pNode = NULL;
	while (pa->next != NULL &&pb != NULL)           //����ͬʱ����
	{
		if (pa->next->exp >pb->exp)
		{	pa = pa->next;
		}
		else if (pa->next->exp == pb->exp)
		{
			 pa->next->coef =pa->next->coef+pb->coef;       //���ϵ��Ϊ�㣬����
			if (0 == pa->next->coef)
			{
				pNode = pa->next;
				pa->next = pNode->next;
				pb = pb->next;
				delete pNode;
				continue;
			}
			pa = pa->next;
			pb = pb->next;
		}
		else
		{
			this->InsertNode(*pb);
			pb = pb->next;
		}
	}
	while (pb != NULL)
	{
		this->InsertNode(*pb);
		pb = pb->next;
	}
}

//����ʽ��������������������
PolyLink & PolyLink::DivLink(PolyLink &L,PolyLink&T)
{
	PolyLink *resLink = new PolyLink;
	PolyNode *pNode = this->head->next;
	PolyNode *rNode = L.head->next;
	PolyNode *tNode = new PolyNode;
	PolyLink *mLink = new PolyLink;
	PolyNode *nNode = new PolyNode;

	while (pNode != NULL)
	{
		mLink->InsertNode(*pNode);
		pNode = pNode->next;                 //��������copy���м����ʽ
	}
	
	pNode = mLink->head->next;
	while(pNode!=NULL)                      //������������������һ�����
	{ 
		
		rNode = L.head->next;
		tNode->coef = pNode->coef / rNode->coef;
		tNode->exp = pNode->exp - rNode->exp;
		if (tNode->exp < 0)
			break;                                    //�����м����һ���ݴ�С�ڳ������һ���������
		tNode->next = NULL;
		resLink->InsertNode(*tNode);
		T.ClearLink();
		while (rNode != NULL)                         //�����������������ʽ��ˣ��õ��м���
		{   
			nNode->coef = -(rNode->coef*tNode->coef);
			nNode->exp = tNode->exp + rNode->exp;
			nNode->next = NULL;
			T.InsertNode(*nNode);                     
			rNode = rNode->next;
		}

		mLink->AddThisLink(T);                         //���м�����ԭ������
		pNode =mLink->head->next;
	}

	T = *mLink;
	delete tNode;
	delete nNode;
	return *resLink;
}

//����ʽ���������̨
void PolyLink::ShowLink()
{
	PolyNode *pNode = head->next;
	while (pNode != NULL)                  
	{   
		cout << pNode->coef << "x^" << pNode->exp;
		pNode = pNode->next;
		if (pNode == NULL)
			continue;
		if (pNode->coef > 0)
			cout << "+";
	}
	cout << endl;

}

//�����������ͷ�ڵ�
void PolyLink::ClearLink()
{
	PolyNode *pNode = head->next;
	while (NULL != head->next)
	{
		pNode = head->next;
		head->next = pNode->next;
		delete pNode;
	}
}

//���ļ���ȡ����ʽ
void ReadText(PolyLink &L,PolyLink &S)
{
	FILE *fp;
	if ((fp = fopen("text.txt", "r")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(1);
	}
	PolyNode *pNode = new PolyNode;
	char s = '`';
	int flag=1;
	int Flag= 1;
	while (!feof(fp))
	{
		float coef;
		int exp;
		char a;
		char b;
		fscanf(fp, " %f %c %c %d", &coef, &a, &b, &exp);
		pNode->coef =flag* coef;
		pNode->exp = exp;
		pNode->next = NULL;
		flag=1;
		if(Flag==0)
	      S.InsertNode(*pNode);            //�ڶ������ʽд��S��
		else
		  L.InsertNode(*pNode);            //�ڶ������ʽд��L��
		s=fgetc(fp);
		if (s == '-')                      //���ϵ������
			flag = -1;
		if (s == '\n')
			Flag = 0;
	}  
	fclose(fp);
	delete pNode;
}

//���������ʽд���ļ�
void WriteText(PolyLink &L)
{
	FILE *fp;
	PolyNode *pNode =new PolyNode;

	if ((fp = fopen("outtext.txt", "a")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(1);
	}
	fputc('\n',fp );
	pNode = L.head->next;
	while (pNode != NULL)
	{    
		
         fprintf(fp, "%.2fx^%d ", pNode->coef, pNode->exp);
		  pNode = pNode->next;
		  if (pNode == NULL)
			  continue;
		 if (pNode->coef > 0)
			fputc('+',fp);
		
	}
	fclose(fp);
	delete pNode;

}
int main()
{  
	PolyLink fir, sec,res,con;
	char op;
	float x,y;
	cout << "welcome!" << endl;
	cout << "l���鿴�ĵ��ж���ʽ" << endl << "e:�˳�" << endl
		<< "+:����ʽ���" << endl << "-:����ʽ���" << endl
		<< "*:����ʽ���" << endl << "/:����ʽ���" << endl;
	
	ReadText(fir, sec);
	while(true)
	{
		cout << "��ѡ��";
		cin >> op;
		getchar();
		switch (op)
		{
		case 'l':
			fir.ShowLink();
			sec.ShowLink();
			cout << "����ʽ��ֵyes/no: y/n ";
			cin >> op;
			if (op == 'y')
			{
				cout <<endl<< "x=";
				cin >> x;
				y = fir.CalLink(x);
				cout << "y1=" << y << endl;
				y = sec.CalLink(x);
				cout << "y2=" << y << endl;
				
			}
			break;

		case '+':
			res = fir.AddLink(sec);
			WriteText(res);
			break;
		case '-':
			res = fir.SubLink(sec);
			WriteText(res);
			break;
		case '*':
			res = fir.MulLink(sec);
			WriteText(res);
			break;
		case '/':
			res = fir.DivLink(sec,con);
			;
			WriteText(res);
			WriteText(con);
			break;
		case 'e':
			exit(0);
		}
	}

}