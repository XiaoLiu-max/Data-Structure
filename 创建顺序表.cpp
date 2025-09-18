#include<iostream>
#include<cassert>
#define Maxsize 50
using namespace std;

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

void Initlist(SqList *&L)
{
	L = new SqList;
	L->length = 0;
}

void Destroylist(SqList *&L)
{
	delete L;
}

bool Listempty(SqList *L)
{
	return L->length == 0;
}

int Listlength(SqList *L)
{
	return L->length;
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

bool GetElem(SqList *L,int i,ElemType &e)
{
	if(i < 1 || i > L->length) return false;
	else
	{
		e = L->data[i-1];
		return true;
	}
}

int LocateElem(SqList *L,ElemType &e)
{
	for(int i=0;i<L->length;++i)
	{
		if(L->data[i] == e)
			return i+1;
		if(i == L->length - 1) return 0;
	}
}

bool ListInsert(SqList *&L,int i,ElemType e)
{
	if(i < 1 || i > L->length)
		return false;
	--i;
	for(int j=L->length;j>i;j--)
	{
		L->data[j] = L->data[j-1];
	}
	L->data[i] = e;
	L->length++;
	return true;
}

bool DeleteElem(SqList *&L,int i,ElemType &e)
{
	if(i < 1 || i > L->length)
		return false;
	--i;
	e = L->data[i];
	for(int j=i;j<L->length-1;++j)
	{
		L->data[j] = L->data[j+1];
	}
	L->length--;
	return true;
}

int main()
{
	SqList* M;
	Initlist(M);
	int n;
	cin >> n;
	ElemType arr[n];
	for(int i=0;i<n;++i)
		cin >> arr[i];
	Creatlist(M,arr,n);
	cout << "是否为空表：" << boolalpha << Listempty(M) << endl;
	cout << "线性表的长度：" << Listlength(M) << endl;
	Printlist(M);
	int m;
	cout << "你要查询第几个元素的值：";
	cin >> m;
	ElemType e;
	if(!GetElem(M,m,e)) cout << "输入数值不符合" << endl;
	else
	{
		cout << "该元素值为：" << e << endl;
	}
	cout << "请输入你要查找的值：" ;
	cin >> e;
	if(!LocateElem(M,e)) cout << "未找到该元素" << endl;
	else cout << "该元素的位置为：" << LocateElem(M,e) << endl;
	cout << "请输入插入元素的位置：";
	cin >> m;
	cout << "请输入新元素的值：";
	cin >> e;
	if(!ListInsert(M,m,e)) cout << "输入位置不符合" << endl;
	else cout << "插入成功！" << endl;
	Printlist(M);
	cout << "请输入删除元素的位置：";
	cin >> m;
	if(!DeleteElem(M,m,e)) cout << "输入位置不符合" << endl;
	else cout << "删除成功！" << endl;
	Printlist(M);
}
