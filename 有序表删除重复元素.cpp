#include<iostream>
using namespace std;
#define Maxsize 50

typedef int ElemType;

typedef struct
{
	ElemType data[Maxsize];
	int length;
}SqList;

typedef struct LinkNode
{
	ElemType data;
	LinkNode *next;
}LinkNode;

void Creatlist(SqList *&L,ElemType a[],int n)
{
	L = new SqList;
	for(int i=0;i<n;++i)
		L->data[i] = a[i];
	L->length = n;
}

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

void Printlist(SqList *L)
{
	if(L->length == 0)
		cout << "此顺序表为空！" << endl;
	else
	{
		for(int i=0;i<L->length;++i)
			cout << L->data[i] << " ";
		cout << endl;
	}
}

void PrintList1(LinkNode *L)
{
	LinkNode *p = L->next;
	while(p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void dels(LinkNode *&L)
{
	LinkNode *p = L->next,*q;
	while(p->next != NULL)
	{
		if(p->data == p->next->data)
		{
			q = p->next;
			p->next = q->next;
			delete q;
		}
		else
			p = p->next;
	}
}

void dels1(SqList *&L)
{
	int k=1,i;
	for(i=1;i<L->length;++i)
	{
		if(L->data[i] != L->data[i-1])
		{
			L->data[k] = L->data[i];
			++k;
		}
	}
	L->length = k;
}

int main()
{
	int choice;
	do
	{
		cout << "\n菜单\n";
		cout << "1.使用顺序表" << endl;
		cout << "2.使用单链表" << endl;
		cout << "0.退出功能" << endl;
		cout << "请选择删除有序表重复元素的方法：";
		cin >> choice;
		switch(choice)
		{
		case 1:
			{
				SqList *L;
				int len;
				cout << "请输入有序表的长度：";
				cin >> len;
				cout << "请输入有序表的元素：";
				ElemType arr[len];
				for(int i=0;i<len;++i)
					cin >> arr[i];
				Creatlist(L,arr,len);
				dels1(L);
				cout << "删除后的有序表：";
				Printlist(L);
				break;
			}
		case 2:
			{
				LinkNode *L;
				int len;
				cout << "请输入有序表的长度：";
				cin >> len;
				cout << "请输入有序表的元素：";
				ElemType arr[len];
				for(int i=0;i<len;++i)
					cin >> arr[i];
				CreateList2(L,arr,len);
				dels(L);
				cout << "删除后的有序表：";
				PrintList1(L);
				break;
			}
		case 0:
			cout << "已退出" << endl;
			break;
		default:
			cout << "输入无效,请重新输入！" << endl;
		}
	}while(choice != 0);
}
