//数据结构实验1，链表实现多项式的四则运算
//2016.10.30

#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

//多项式结点
struct PolyNode
{  
	float coef;
	int  exp;
	PolyNode * next;
};

//多项式类
class PolyLink
{   
public:
	PolyLink() { head = new PolyNode;
	             head->next = NULL;              //建立多项式
	            }
	~PolyLink() { ClearLink(); delete head; }    //清空多项式

	void  SortLink();                            //降幂排序
	float CalLink(float x);                      //定点求值
	int   InsertNode(PolyNode& node);            // 插入函数
	
	PolyLink & AddLink(PolyLink &L1);             //+
	PolyLink & SubLink(PolyLink &L);              //-
	PolyLink & MulLink(PolyLink &L);              //*
	PolyLink & DivLink(PolyLink &L,PolyLink &T);  // /
	void AddThisLink(PolyLink &L);                //多项式相加到加项中
	void ShowLink();                             // 控制台输出
	void ClearLink();                             //清空


	PolyNode *head;                            //头结点
};


// 按降幂排序 ，选择排序
// 未交换节点位置，系数交换
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
				temp2 = pNode->exp;            //直接交换系数和幂次
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

//定点求值函数
float PolyLink::CalLink(float x)
{
	float sum=0;
	PolyNode *pNode = head->next;
	while (pNode != NULL)
	{
		float a=pNode->coef;
		int b=pNode->exp;
		sum = sum + a* pow(x, b);      //迭代求值
		pNode = pNode->next;
	}
	return sum;
}

//插入函数
//按幂次插入到结点该在的位置，如果原来链表中有该幂次，系数相加
int  PolyLink::InsertNode(PolyNode & node)
{
	PolyNode * pNode = new PolyNode;
	PolyNode *tNode = this->head;
	pNode->exp = node.exp;
	pNode->coef = node.coef;
	pNode->next = NULL;
	if (tNode->next == NULL)
	{                                     //如果链表为空，插入到第一位
		tNode->next = pNode;
		return 1;                     
	}
	while (tNode->next != NULL)
	{
		if (tNode->next->exp < pNode->exp)
		{   
			pNode->next = tNode->next;
			tNode->next = pNode;	                 //找到位置并插入
			return 1;
		}
		if (tNode->next->exp == pNode->exp)
		{
			tNode->next->coef += pNode->coef;         //同幂次直接相加
			if (tNode->next->coef == 0)
			{   
				pNode = tNode->next;
				tNode->next = pNode->next;             //相加为零，删除结点
				delete pNode;
			}
			return 1;
		}
		tNode = tNode->next;
	}
	tNode->next = pNode;
	return 1;
}

//多项式相加，返回新的链表，不改变原项

PolyLink& PolyLink::AddLink(PolyLink &L1)
{
	PolyLink *resLink = new PolyLink;       //存储结果多项式
	PolyNode *pa = L1.head->next; 
	PolyNode *pb = this->head->next;
	while (pa != NULL &&pb != NULL)         //遍历相加
	{   
		if (pa->exp > pb->exp)
		{   
			resLink->InsertNode(*pa);       //高幂次的先插入
			pa = pa->next;
		}
		else if (pa->exp==pb->exp)
		{   
			PolyNode *pNode = new PolyNode;         //同幂次系数相加
			pNode->coef = pa->coef + pb->coef;
			pNode->exp = pa->exp; 
			pNode->next = NULL;
			if (0 == pNode->coef)                //相加系数为零，则不添加
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
	while (pa != NULL)               //将两项余项添加到结果多项式
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

//多项式相减，返回新的多项式
PolyLink & PolyLink::SubLink(PolyLink &L)
{
	PolyLink *resLink = new PolyLink;            //存结果多项式
	PolyNode *pa = this->head->next;
	PolyNode *pb = L.head->next;

	while (pb != NULL)
	{
		pb->coef = -pb->coef;
		pb = pb->next;                      //将原加数系数取反
	}

	*resLink = this->AddLink(L);            //调用加法运算

	pb = L.head->next;
	while (pb != NULL)
	{
		pb->coef = -pb->coef;               //将原加数复原
		pb = pb->next;
	}

	return *resLink;
}

//多项式相乘，返回新多项式
//第二项的每一项依次与前者相乘，再插入
PolyLink& PolyLink::MulLink(PolyLink &L)
{
	PolyLink *resLink = new PolyLink;         //存结构多项式
	PolyLink *pLink = new PolyLink;
	PolyNode *pNode = this->head->next;       
	PolyNode *tNode = L.head->next;
	PolyNode *rNode = new PolyNode;
	while (tNode != NULL)
	{   
		pNode = this->head->next;
		while (pNode != NULL)                //第二个多项式依次与第一项相乘
		{   
			rNode->coef = 0;             
			rNode->exp = 0;
			rNode->coef = tNode->coef*pNode->coef;
			rNode->exp = tNode->exp+pNode->exp;
			rNode->next = NULL;
			pLink->InsertNode(*rNode);         //相乘结果加到中间链表
			pNode = pNode->next;
		}
	
		resLink->AddThisLink(*pLink);           //将每项多项式加到结果多项式中
		pLink->ClearLink();                     //清空中间多项式
		tNode =tNode->next;

	}
	delete pLink;
	delete rNode;
	return *resLink;		
}

//多项式相加，不返回新链表，返回到当前多项式中
void PolyLink::AddThisLink(PolyLink&L)
{   
	PolyNode *pb = L.head->next;
	PolyNode *pa = this->head;
	PolyNode *pNode = NULL;
	while (pa->next != NULL &&pb != NULL)           //两项同时遍历
	{
		if (pa->next->exp >pb->exp)
		{	pa = pa->next;
		}
		else if (pa->next->exp == pb->exp)
		{
			 pa->next->coef =pa->next->coef+pb->coef;       //相加系数为零，跳过
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

//多项式相除，商与余项返回新链表
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
		pNode = pNode->next;                 //将除数项copy到中间多项式
	}
	
	pNode = mLink->head->next;
	while(pNode!=NULL)                      //被除项依次与除数项第一项相除
	{ 
		
		rNode = L.head->next;
		tNode->coef = pNode->coef / rNode->coef;
		tNode->exp = pNode->exp - rNode->exp;
		if (tNode->exp < 0)
			break;                                    //待到中间项第一项幂次小于除数项第一项，结束除法
		tNode->next = NULL;
		resLink->InsertNode(*tNode);
		T.ClearLink();
		while (rNode != NULL)                         //将相除结果与除数多项式相乘，得到中间项
		{   
			nNode->coef = -(rNode->coef*tNode->coef);
			nNode->exp = tNode->exp + rNode->exp;
			nNode->next = NULL;
			T.InsertNode(*nNode);                     
			rNode = rNode->next;
		}

		mLink->AddThisLink(T);                         //将中间项与原项作差
		pNode =mLink->head->next;
	}

	T = *mLink;
	delete tNode;
	delete nNode;
	return *resLink;
}

//多项式输出到控制台
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

//清空链表，保留头节点
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

//从文件读取多项式
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
	      S.InsertNode(*pNode);            //第二项多项式写入S中
		else
		  L.InsertNode(*pNode);            //第二项多项式写入L中
		s=fgetc(fp);
		if (s == '-')                      //标记系数正负
			flag = -1;
		if (s == '\n')
			Flag = 0;
	}  
	fclose(fp);
	delete pNode;
}

//将结果多项式写入文件
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
	cout << "l：查看文档中多项式" << endl << "e:退出" << endl
		<< "+:多项式相加" << endl << "-:多项式相减" << endl
		<< "*:多项式相乘" << endl << "/:多项式相除" << endl;
	
	ReadText(fir, sec);
	while(true)
	{
		cout << "请选择：";
		cin >> op;
		getchar();
		switch (op)
		{
		case 'l':
			fir.ShowLink();
			sec.ShowLink();
			cout << "多项式求值yes/no: y/n ";
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