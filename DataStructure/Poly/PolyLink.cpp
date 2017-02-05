#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;
int po[5][2] = { 1,1,2,2,3,3,4,4,5,5 };

struct PolyNode
{  
	float coef;
	int  exp;
	PolyNode * next;
};

class PolyLink
{   
public:
	PolyLink() { head = new PolyNode;
	             head->next = NULL;
	              currNode = head;
	            }
	~PolyLink() { ClearLink(); delete head; }
	void MakeLink();
	void SortLink();
	float CalLink(float x);
	void InsertNode(PolyNode& node);
	
	PolyLink & AddLink(PolyLink &L1);
	PolyLink & SubLink(PolyLink &L);
	PolyLink & MulLink(PolyLink &L);
	PolyLink & DivLink(PolyLink &L,PolyLink &T);
	void AddThisLink(PolyLink &L);
	void ShowLink();
	void ClearLink();


	PolyNode *head;
	PolyNode *currNode;
};


void PolyLink::MakeLink()
{
	int j = 0;
	PolyNode *pNode=NULL;
	
	for (j = 0; j < 5; j++)
	{
		  if(po[j][0] != 0 )
			{
				pNode = new PolyNode;
				pNode->coef = po[j][0];
				pNode->exp = po[j][1];
				pNode->next = NULL;
				currNode->next = pNode;
				currNode = currNode->next;
			}
	}

		
}
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
				temp2 = pNode->exp;
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
float PolyLink::CalLink(float x)
{
	float sum=0;
	PolyNode *pNode = head->next;
	while (pNode != NULL)
	{
		float a=pNode->coef;
		int b=pNode->exp;
		sum = sum + a* pow(x, b);
		pNode = pNode->next;
	}
	return sum;
}

void PolyLink::InsertNode(PolyNode & node)
{
	PolyNode * pNode = new PolyNode;
	pNode->coef = node.coef;
	pNode->exp = node.exp;
	pNode->next = NULL;
	this->currNode->next = pNode;
	currNode = currNode->next;
	

}
PolyLink& PolyLink::AddLink(PolyLink &L1)
{
	PolyLink *resLink = new PolyLink;
	PolyNode *pa = L1.head->next;
	PolyNode *pb = this->head->next;
	while (pa != NULL &&pb != NULL)
	{   

		if (pa->exp > pb->exp)
		{   
			resLink->InsertNode(*pa);
			pa = pa->next;
		}
		else if (pa->exp==pb->exp)
		{   
			PolyNode *pNode = new PolyNode;
			pNode->coef = pa->coef + pb->coef;
			pNode->exp = pa->exp;
			pNode->next = NULL;
			if (0 == pNode->coef)
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
	while (pa != NULL)
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

PolyLink & PolyLink::SubLink(PolyLink &L)
{
	PolyLink *resLink = new PolyLink;
	PolyNode *pa = this->head->next;
	PolyNode *pb = L.head->next;

	while (pa != NULL &&pb != NULL)
	{
		if (pa->exp > pb->exp)
		{
			resLink->InsertNode(*pa);
			pa = pa->next;
		}
		else if (pa->exp == pb->exp)
		{
			if (pa->coef == pb->coef)
			{
				pa = pa->next;
				pb = pb->next;
				continue;
			}
			PolyNode *pNode = new PolyNode;
			pNode->coef = pa->coef- pb->coef;
			pNode->exp = pa->exp;
			pNode->next = NULL;
			resLink->InsertNode(*pNode);
			pa = pa->next;
			pb = pb->next;
			delete pNode;
		}
		else
		{
			PolyNode *pNode = new PolyNode;
			pNode->coef = -( pb->coef);
			pNode->exp = pa->exp;
			pNode->next = NULL;
			resLink->InsertNode(*pNode);
			pb = pb->next;	
			delete pNode;
		}
	}
	while (pa != NULL)
	{
		resLink->InsertNode(*pa);
		pa = pa->next;
	}
	while (pb != NULL)
	{   
		PolyNode *pNode = new PolyNode;
		pNode->coef = -(pb->coef);
		pNode->exp = pb->exp;
		pNode->next = NULL;
		resLink->InsertNode(*pb);
		pb = pb->next;
	}
	return *resLink;


}
PolyLink& PolyLink::MulLink(PolyLink &L)

{
	PolyLink *resLink = new PolyLink;
	PolyLink *pLink = new PolyLink;

	PolyNode *pNode = this->head->next;
	PolyNode *tNode = L.head->next;
	PolyNode *rNode = new PolyNode;
	while (tNode != NULL)
	{   
		pNode = this->head->next;
		while (pNode != NULL)
		{   
			rNode->coef = 0;
			rNode->exp = 0;
			rNode->coef = tNode->coef*pNode->coef;
			rNode->exp = tNode->exp+pNode->exp;
			rNode->next = NULL;
			pLink->InsertNode(*rNode);
			pNode = pNode->next;
		}
	
		resLink->AddThisLink(*pLink);
		pLink->ClearLink();
		tNode =tNode->next;

	}
	delete pLink;
	delete rNode;
	return *resLink;

			
}
void PolyLink::AddThisLink(PolyLink&L)
{   
	
	PolyNode *pb = L.head->next;
	PolyNode *pa = this->head->next;
	PolyNode *pNode = NULL;
	while (pa != NULL &&pb != NULL)
	{

		if (pa->exp >pb->exp)
		{
			pa = pa->next;
		}
		else if (pa->exp == pb->exp)
		{
			 pa->coef =pa->coef+pb->coef;
			if (0 == pa->coef)
			{
				pNode = pa;
				pa = pa->next;
				this->head->next = pa;
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

PolyLink & PolyLink::DivLink(PolyLink &L,PolyLink&T)
{
	PolyLink *resLink = new PolyLink;
	PolyNode *pNode = this->head->next;
	PolyNode *rNode = L.head->next;
	PolyNode *tNode = new PolyNode;
	PolyLink *wLink = new PolyLink;
	PolyLink *mLink = new PolyLink;
	PolyNode *nNode = new PolyNode;

	while (pNode != NULL)
	{
		T.InsertNode(*pNode);
		pNode = pNode->next;
	}
	
	pNode = T.head->next;
	while(pNode!=NULL)
	{   
		rNode = L.head->next;
		tNode->coef = pNode->coef / rNode->coef;
		tNode->exp = pNode->exp - rNode->exp;
		tNode->next = NULL;
		resLink->InsertNode(*tNode);
		
		while (rNode != NULL)
		{   
			nNode->coef = -(rNode->coef*tNode->coef);
			nNode->exp = tNode->exp + rNode->exp;
			nNode->next = NULL;
			mLink->InsertNode(*nNode);
			rNode = rNode->next;
		}
		mLink->SortLink();
		T.AddThisLink(*mLink);
		mLink->ClearLink();
		pNode = pNode->next;
	}
	return *resLink;
}
void PolyLink::ShowLink()
{
	PolyNode *pNode = head->next;
	while (pNode != NULL)
	{   
		cout << pNode->coef << "x^" << pNode->exp << " ";
		pNode = pNode->next;
	}
	cout << endl;

}

void PolyLink::ClearLink()
{
	PolyNode *pNode = head->next;
	while (NULL != head->next)
	{
		pNode = head->next;
		head->next = pNode->next;
		delete pNode;
	}
	currNode = head;

}


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
	      S.InsertNode(*pNode);
		else
		  L.InsertNode(*pNode);

		s=fgetc(fp);
		if (s == '-')
			flag = -1;
		if (s == ';')
			Flag = 0;
	}  
	fclose(fp);
	delete pNode;
}

void WriteText(PolyLink &L)
{
	FILE *fp;
	PolyNode *pNode =new PolyNode;

	if ((fp = fopen("text.txt", "a")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(1);
	}
	fputc('\n',fp );
	pNode = L.head->next;
	while (pNode != NULL)
	{    
		if (pNode->coef > 0)
			fputc('+',fp);
         fprintf(fp, "%.1fx^%d ", pNode->coef, pNode->exp);
		 
		 pNode = pNode->next;
	}
	fclose(fp);
	delete pNode;

}
int main()
{
	PolyLink L1,L2,L3,L4,L5,L6;

	ReadText(L1,L2);

	L1.SortLink();
	L1.ShowLink();
    L2.SortLink();
    L2.ShowLink();
	L3 = L1.SubLink(L2);
	L3.ShowLink();
	L4= L1.MulLink(L2);	
	L4.SortLink();
	L4.ShowLink();
	L5 = L4.DivLink(L1, L6);
	L5.ShowLink();
	L6.ShowLink();
	//WriteText(L3);
}