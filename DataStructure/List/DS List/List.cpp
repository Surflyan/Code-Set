//2016.10.22  
//���������

#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node * next;

};


template <typename T>
class List
{
public:
	List()
	{
		head = new Node<T>;
		head->data = 0;
		head->next = NULL;
	}

	~List() {ClearList(); delete head;}
	bool Insert(T x);                       //���β����
	bool Insert(T x, int position);         //ָ��λ�ò���
	bool Delete(T x);                       //ɾ����һ�γ��ֵ�ĳֵ
	int Position(T x);                       //ĳֵ��һ�γ��ֵ�λ��
	Node<T>* Locate(int pos);                //ĳλ�õ�ǰһ���
	bool IsEmpty();                           //�ж��Ƿ�Ϊ��
	void ShowList();                           //��ӡ����
	void ClearList();                         //���������ͷ�ڵ�
	int  GetListLen();                          //������
private:
	Node<T>  *head;
	int listLen = 0;                           //��¼������
};

//2016.10.22   15.40
//������β������һ���µĽڵ�
template<typename T>
bool List<T>::Insert(T x)
{
	Node<T> *newNode;
	Node<T> *pNode;

	newNode = new Node<T>;
	pNode = head;

	while (pNode->next!= NULL)
	{
		pNode = pNode->next;
	}
	newNode->data = x;
	newNode->next = NULL;
	pNode->next = newNode;
	this->listLen++;
	return true;
}


//�������м����һ���ڵ�
template <typename T>
bool List<T>::Insert(T x, int position)
{   
	if (position > this->listLen)
		return false;
	Node<T> *pNode = Locate(position);
	Node<T> *newNode = new Node<T>;
	newNode->data = x;
	newNode->next= pNode->next;
	pNode->next = newNode;

	this->listLen++;
	return true;

}



//����ָ��λ�÷��ظ�λ�õ�ǰһ�ڵ�
template <typename T>
Node<T>* List<T>::Locate(int position)
{
	 Node<T> *p;
	 p = this->head;
	 int i = 0;

     if (position < 0)
	      return NULL;
	 while (p!=NULL&& i < position-1)
	 {
	     p = p->next;
	     i++;
	 }

   return p;

}


//ɾ��һ��Ԫ��
template <typename T>
bool List<T>::Delete(T x)
{
	int pos = 0;
	pos = this->Position(x);

	Node<T> *pNode = this->Locate(pos);
	Node<T> *delNode = pNode->next;
	pNode->next =delNode->next;

	delete delNode;
	return true;

}

//����ֵΪx���ֵ�λ��,�������ڴ�Ԫ���򷵻�-1
template <typename T>
int List<T>::Position(T x)
{   
	int i=0;
	if (this->IsEmpty())
		return -1;
	Node<T>* pNode = head->next;
	i++;
	while (pNode->data != x)
	{   
		pNode = pNode->next;
		i++;
		if (i > this->listLen)
			return -1;
	}
	
	
 
	return i;																	   

}

template<typename T>
bool List<T>::IsEmpty()
{  
	if (head->next == NULL)
		return true;
	else
		return false;
}

//�������


template <typename T>
void List<T>::ShowList()
{
	Node<T> *pNode = head->next;
	while (NULL != pNode)
	{
		cout << pNode->data << "   ";
		pNode = pNode->next;
	}
	cout << endl;
	
}

//�����������ͷ�ڵ�
template<typename T>
void List<T>::ClearList()
{
	Node<T> *pNode = head;
	while (NULL != head->next)
	{
		pNode = head->next;
		head->next = pNode->next;
		delete pNode;
	}
	

}
template <typename T>
int List<T>::GetListLen()
{
	return this->listLen;
}
void main()
{
	List<int> L;
	cout<<L.Position(9)<<endl;
	L.Insert(1);			 
	L.Insert(3);
	L.Insert(4);
	L.Insert(5);
	L.ShowList();
	L.Insert(2, 1);
	L.Insert(0,4);
	L.ShowList();
	L.Delete(0);
	L.Delete(5);
	L.ShowList();

	
  
}