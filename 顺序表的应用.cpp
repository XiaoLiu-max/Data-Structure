#include<iostream>
using namespace std;
#define Maxsize 50

typedef int ElemType;

typedef struct
{
	ElemType data[Maxsize];
	int length;
}SqList;

void Creatlist(SqList *&L,ElemType a[],int n)
{
	L = new SqList;
	for(int i=0;i<n;++i)
		L->data[i] = a[i];
	L->length = n;
}

void Printlist(SqList *L)
{
	if(L->length == 0) cout << "此顺序表为空" << endl;
	else
	{
		for(int i=0;i<L->length;++i)
			cout << L->data[i] << " ";
		cout << endl;
	}
}

void DeleteX1(SqList *&L,ElemType x)           //整体建表法
{
	int k=0;
	for(int i=0;i<L->length;++i)
	{
		if(L->data[i] != x)
		{
			L->data[k] = L->data[i];
			k++;
		}
	}
	L->length = k;
}

void DeleteX2(SqList *&L,ElemType x)           //元素移动法
{
	int k=0;
	for(int i=0;i<L->length;++i)
	{
		if(L->data[i] == x)
			++k;
		else
			L->data[i-k] = L->data[i];
	}
	L->length -= k;
}

void partition1(SqList *&L)                  //元素交换法
{
	int i=0,j=L->length - 1;
	ElemType base = L->data[0];
	while(i<j)
	{
		while(i<j && L->data[j] > base)
			--j;
		while(i<j && L->data[i] <= base)
			++i;
		if(i<j)
			swap(L->data[i],L->data[j]);
	}
	swap(L->data[0],L->data[i]);
}

void partition2(SqList *&L)                  
{
	int i=0,j=L->length-1;
	ElemType base = L->data[0];
	while(i<j)
	{
		while(i<j && L->data[j]>base)
			--j;
		L->data[i] = L->data[j];
		while(i<j && L->data[i]<=base)
			++i;
		L->data[j] = L->data[i];
	}
	L->data[i] = base;
}

void move1(SqList *&L)
{
	int i=0,j=L->length - 1;
	while(i<j)
	{
		while(i<j && L->data[j]%2==0)
			--j;
		while(i<j && L->data[i]%2!=0)
			++i;
		if(i<j) swap(L->data[i],L->data[j]);
	}
}

void move2(SqList *&L)
{
	int i=-1;
	for(int j=0;j<L->length;++j)
	{
		if(L->data[j]%2 == 1)
		{
			++i;
			if(i != j)
				swap(L->data[i],L->data[j]);
		}
	}
}

int main()
{
	int n;
	cin >> n;
	ElemType arr[n];
	ElemType e;
	for(int i=0;i<n;++i)
		cin >> arr[i];
	SqList *M;
	Creatlist(M,arr,n);
//	cout << "请输入你要删除的元素值：" ;
//	cin >> e;
//	DeleteX1(M,e);
//	Printlist(M);
//	cout << "请输入你要删除的元素值：" ;
//	cin >> e;
//	DeleteX2(M,e);
//	Printlist(M);
	partition1(M);
	Printlist(M);
	partition2(M);
	Printlist(M);
//	move1(M);
//	Printlist(M);
//	move2(M);
//	Printlist(M);
}
