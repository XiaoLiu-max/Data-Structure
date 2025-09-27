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

void UnionList(SqList *LA,SqList *LB,SqList *&LC)
{
	int i=0,j=0,k=0;
	LC = new SqList;
	while(i<LA->length && j<LB->length)
	{
		if(LA->data[i] < LB->data[j])
		{
			LC->data[k] = LA->data[i];
			++i;++k;
		}
		else
		{
			LC->data[k] = LB->data[j];
			++j;++k;
		}
	}
	while(i<LA->length)
	{
		LC->data[k] = LA->data[i];
		++i;++k;
	}
	while(j<LB->length)
	{
		LC->data[k] = LB->data[j];
		++j;++k;
	}
	LC->length = k;
}

void UnionList1(LinkNode *LA,LinkNode *LB,LinkNode *&LC)
{
	LinkNode *pa,*pb,*r,*s;
	pa = LA->next;pb = LB->next;
	LC = new LinkNode;
	r = LC;
	while(pa != NULL && pb != NULL)
	{
		if(pa->data < pb->data)
		{
			s = new LinkNode;
			s->data = pa->data;
			r->next = s;
			r = s;
			pa = pa->next;
		}
		else
		{
			s = new LinkNode;
			s->data = pb->data;
			r->next = s;
			r = s;
			pb = pb->next;
		}
	}
	while(pa != NULL)
	{
		s = new LinkNode;
		s->data = pa->data;
		r->next = s;
		r = s;
		pa = pa->next;
	}
	while(pb != NULL)
	{
		s = new LinkNode;
		s->data = pb->data;
		r->next = s;
		r = s;
		pb = pb->next;
	}
}

int main()
{
//	SqList *LA,*LB,*LC;
	LinkNode *LA,*LB,*LC;
	int len,len1;
	cout << "请输入第一个有序表LA的长度：";
	cin >> len;
	ElemType arr[len],e;
	cout << "请输入第一个有序表LA的元素：";
	for(int i=0;i<len;++i)
		cin >> arr[i];
	cout << "请输入第二个有序表LB的长度：";
	cin >> len1;
	ElemType arr1[len1];
	cout << "请输入第二个有序表LB的元素：";
	for(int i=0;i<len1;++i)
		cin >> arr1[i];
//	Creatlist(LA,arr,len);Creatlist(LB,arr1,len1);
//	UnionList(LA,LB,LC);
//	Printlist(LC);
	CreateList2(LA,arr,len);CreateList2(LB,arr1,len1);
	UnionList1(LA,LB,LC);
	PrintList1(LC);
}
