#include<iostream>
using namespace std;

typedef int ElemType;

typedef struct LinkNode
{
	ElemType data;
	LinkNode *next;
}LinkNode;

void CreateList1(LinkNode *&L,ElemType a[],int n)          //头插法
{
	LinkNode *s;
	L = new LinkNode;
	L->next = NULL;
	for(int i=0;i<n;++i)
	{
		s = new LinkNode;
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

void CreateList2(LinkNode *&L,ElemType a[],int n)          //尾插法
{
	LinkNode *s,*r;
	L = new LinkNode;
	L->next = NULL;
	r = L;
	for(int i=0;i<n;++i)
	{
		s = new LinkNode;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

void InitList(LinkNode *&L)
{
	L = new LinkNode;
	L->next = NULL;
}

void DestroyList(LinkNode *&L)
{
	LinkNode *pre = L,*p = L->next;
	while(p != NULL)
	{
		delete pre;
		pre = p;
		p = p->next;
	}
	delete pre;
}

bool Listempty(LinkNode *L)
{
	return L->next == NULL;
}

int Listlength(LinkNode *L)
{
	int i=0;
	LinkNode *p = L;
	while(p->next != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

void PrintList(LinkNode *L)
{
	LinkNode *p = L->next;
	while(p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

bool GetElem(LinkNode *L,int i,ElemType e)
{
	LinkNode *p = L;
	if(i <= 0) return false;
	for(int j=0;j<i;++j)
	{
		p = p->next;
		if(p == NULL) return false;
	}
	e = p->data;
	return true;
}

int LocateElem(LinkNode *L,ElemType e)
{
	LinkNode *p = L->next;
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

bool ListInsert(LinkNode *&L,int i,ElemType e)
{
	if( i<= 0) return false;
	LinkNode *p = L,*s;
	for(int j=0;j<i-1;++j)
	{
		p = p->next;
		if(p == NULL) return  false;
	}
	s = new LinkNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool DeleteElem(LinkNode *&L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p = L,*q;
	if(i<=0) return false;
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
		p->next = q->next;
		e = q->data;
		delete q;
		return true;
	}
}

int main()
{
	LinkNode *M;
	InitList(M);
	int length,choice,n;
	cout << "请输入链表的初始长度：";
	cin >> length;
	ElemType arr[length];
	ElemType e;
	cout << "请输入链表元素：";
	for(int i=0;i<length;++i)
		cin >> arr[i];
	CreateList2(M,arr,length);
	do
	{
		cout << "\n菜单\n";
		cout << "1.判断线性表是否为空表" << endl;
		cout << "2.求线性表的长度" << endl;
		cout << "3.输出线性表" << endl;
		cout << "4.按序号求线性表中元素" << endl;
		cout << "5.按元素值查找" << endl;
		cout << "6.插入数据元素" << endl;
		cout << "7.删除数据元素" << endl;
		cout << "0.退出" << endl;
		cout << "请选择对应功能：";
		cin >> choice;
		switch(choice)
		{
		case 1:
			cout << boolalpha << Listempty(M) << endl;
			break;
		case 2:
			cout << Listlength(M) << endl;
			break;
		case 3:
			PrintList(M);
			break;
		case 4:
			cout << "请输入要查找元素的序号：" ;
			cin >> n;
			if(!GetElem(M,n,e)) cout << "输入无效！" << endl;
			else cout << "该位置元素为：" << e << endl;
			break;
		case 5:
			cout << "请输入你要查找的元素值：" ;
			cin >> e;
			if(!LocateElem(M,e)) cout << "未找到该元素" << endl;
			else cout << "该元素位置为：" << LocateElem(M,e) << endl;
			break;
		case 6:
			cout << "请输入你要插入元素的位置：";
			cin >> n;
			cout << "请输入你要插入元素的值：" ;
			cin >> e;
			if(!ListInsert(M,n,e)) cout << "插入失败" << endl;
			else cout << "插入成功" << endl;
			break;
		case 7:
			cout << "请输入你要删除元素的位置：" ;
			cin >> n;
			if(!DeleteElem(M,n,e)) cout << "删除失败" << endl;
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
