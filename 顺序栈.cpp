#include<iostream>
using namespace std;
#define Maxsize 50

typedef int ElemType;

typedef struct
{
	ElemType data[Maxsize];
	int top;            //存放栈顶元素在data数组中的下标
}SqStack;

void InitStack(SqStack *&s)
{
	s = new SqStack;
	s->top = -1;
}

void DestroyStack(SqStack *&s)
{
	delete s;
}

bool StackEmpty(SqStack *s)
{
	return s->top == -1;
}

bool Push(SqStack *&s,ElemType e)
{
	if(s->top == Maxsize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s,ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack *s,ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

bool symmetry(ElemType str[])
{
	ElemType e;
	SqStack *st;
	InitStack(st);
	for(int i=0;str[i]!='\0';++i)
		Push(st,str[i]);
	for(int i=0;str[i]!='\0';++i)
	{
		Pop(st,e);
		if(str[i] != e)
		{
			DestroyStack(st);
			return false;
		}
	}
	DestroyStack(st);
	return true;
}

int main()
{
	int n,choice;
	cout << "请输入栈元素个数：";
	cin >> n;
	ElemType arr[n],e;
	SqStack *s;
	InitStack(s);
	cout << "请输入栈元素值：";
	for(int i=0;i<n;++i)
	{
		cin >> arr[i];
		Push(s,arr[i]);
	}
	do
	{
		cout << "\n菜单\n" ;
		cout << "1.判断栈是否为空" << endl;
		cout << "2.进栈" << endl;
		cout << "3.出栈" << endl;
		cout << "4.取栈顶元素" << endl;
		cout << "5.判断是否为对称栈" << endl;
		cout << "0.退出" << endl;
		cin >> choice;
		switch(choice)
		{
		case 1:
			cout << boolalpha << StackEmpty(s) << endl;
			break;
		case 2:
			cout << "请输入进栈元素：";
			cin >> e;
			if(Push(s,e)) cout << "进栈成功！" << endl;
			else cout << "进栈失败！" << endl;
			break;
		case 3:
			if(Pop(s,e)) cout << "出栈成功！栈顶元素为："  << e << endl;
			else cout << "出栈失败！" << endl;
			break;
		case 4:
			if(GetTop(s,e)) cout << "栈顶元素为：" << e << endl;
			else cout << "此栈为空！" << endl;
			break;
		case 5:
			cout << boolalpha << symmetry(arr) << endl;
			break;
		case 0:
			DestroyStack(s);
			cout << "已退出" << endl;
			break;
		default:
			cout << "输入无效，请重新输入！" << endl;
		}
	}while(choice != 0);
}
