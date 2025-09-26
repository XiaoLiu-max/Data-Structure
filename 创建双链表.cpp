#include<iostream>
using namespace std;

typedef int Elemtype;

typedef struct DLinkNode
{
	Elemtype data;
	DLinkNode *prior;
	DLinkNode *next;
}DLinkNode;

void CreateList1(DLinkNode *&L,Elemtype a[],int n)
{
	DLinkNode *s;
	L = new DLinkNode;
	L->prior = L->next = NULL;
	for(int i=0;i<n;++i)
	{
		s = new DLinkNode;
		s->data = a[i];
		s->next = L->next;
		if(L->next != NULL)
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	}
}

void CreateList2(DLinkNode *&L,Elemtype a[],int n)
{
	DLinkNode *s,*r;
	L = new DLinkNode;
	r = L;
	for(int i=0;i<n;++i)
	{
		s = new DLinkNode;
		s->data = a[i];
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = NULL;
}

bool Listinsert(DLinkNode *&L,int i,Elemtype e)
{
	int j=0;
	DLinkNode *s,*p = L;
	if(i<0) return false;
	while(j<i-1 && p!=NULL)
	{
		++j;
		p = p->next;
	}
	if(p == NULL) return false;
	else
	{
		s = new DLinkNode;
		s->data = e;
		s->next = p->next;
		if(p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

bool Listdelete(DLinkNode *&L,int i,Elemtype &e)
{
	int j=0;
	DLinkNode *p = L,*q;
	if(i<0) return false;
	while(j<i-1 && p!=NULL)
	{
		++j;
		p = p->next;
	}
	if(p == NULL) return false;
	else
	{
		q = p->next;
		if(q == NULL) return false;
		e = p->data;
		p->next = q->next;
		if(q->next != NULL)
			q->next->prior = p;
		delete q;
	}
}

int Listlength(DLinkNode *L)
{
	int length = 0;
	DLinkNode *p = L;
	while(p->next != NULL)
	{
		length++;
		p = p->next;
	}
	return length;
}

bool GetElem(DLinkNode *L,int i,Elemtype &e)
{
	DLinkNode *p = L;
	for(int j=0;j<i;++j)
	{
		p = p->next;
		if(p->next == NULL)
			return false;
	}
	e = p->data;
	return true;
}

int LocateElem(DLinkNode *L,Elemtype e)
{
	DLinkNode *p = L->next;
	int i = 1;
	while(p != NULL)
	{
		if(p->data == e) return i;
		else 
		{
			p = p->next;
			++i;
		}
	}
	return 0;
}

void DestroyList(DLinkNode *&L)
{
	DLinkNode *pre = L,*p = L->next;
	while(p != NULL)
	{
		delete pre;
		pre = p;
		p = p->next;
	}
	delete pre;
}

void PrintList(DLinkNode *L)
{
	DLinkNode *p = L->next;
	while(p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

int main()
{
	DLinkNode *M;
	int length,choice,n;
	cout << "请输入链表的初始长度：";
	cin >> length;
	Elemtype arr[length];
	Elemtype e;
	cout << "请输入链表元素：";
	for(int i=0;i<length;++i)
		cin >> arr[i];
	CreateList2(M,arr,length);
	do
	{
		cout << "\n菜单\n";
		cout << "1.求线性表的长度" << endl;
		cout << "2.输出线性表" << endl;
		cout << "3.按序号求线性表中元素" << endl;
		cout << "4.按元素值查找" << endl;
		cout << "5.插入数据元素" << endl;
		cout << "6.删除数据元素" << endl;
		cout << "0.退出" << endl;
		cout << "请选择对应功能：";
		cin >> choice;
		switch(choice)
		{
		case 1:
			cout << Listlength(M) << endl;
			break;
		case 2:
			PrintList(M);
			break;
		case 3:
			cout << "请输入要查找元素的序号：" ;
			cin >> n;
			if(!GetElem(M,n,e)) cout << "输入无效！" << endl;
			else cout << "该位置元素为：" << e << endl;
			break;
		case 4:
			cout << "请输入你要查找的元素值：" ;
			cin >> e;
			if(!LocateElem(M,e)) cout << "未找到该元素" << endl;
			else cout << "该元素位置为：" << LocateElem(M,e) << endl;
			break;
		case 5:
			cout << "请输入你要插入元素的位置：";
			cin >> n;
			cout << "请输入你要插入元素的值：" ;
			cin >> e;
			if(!Listinsert(M,n,e)) cout << "插入失败" << endl;
			else cout << "插入成功" << endl;
			break;
		case 6:
			cout << "请输入你要删除元素的位置：" ;
			cin >> n;
			if(!Listdelete(M,n,e)) cout << "删除失败" << endl;
			else cout << "删除成功,你删除元素的值为：" << e << endl;
			break;
		case 0:
			DestroyList(M);
			cout << "已退出" << endl;
			break;
		default:
			cout << "无效选择，请重新输入！" << endl;
		}
	}while(choice != 0);
}
