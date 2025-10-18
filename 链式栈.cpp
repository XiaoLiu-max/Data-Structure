#include<iostream>
#include<string>
#include<cstring>
#include<limits>
using namespace std;

typedef char ElemType;

typedef struct linknode
{
	ElemType data;
	struct linknode *next;
}LinkStNode;

void InitStack(LinkStNode *&s)
{
	s = new LinkStNode;
	s->next = NULL;
}

void DestroyStack(LinkStNode *&s)
{
	LinkStNode *pre = s,*p = s->next;
	while(p != NULL)
	{
		delete pre;
		pre = p;
		p = p->next;
	}
	delete pre;
}

bool StackEmpty(LinkStNode *s)
{
	return s->next == NULL;
}

bool Push(LinkStNode *&s,ElemType e)
{
	LinkStNode *p;
	p = new LinkStNode;
	p->data = e;
	p->next = s->next;
	s->next = p;
	return true;
}

bool Pop(LinkStNode *&s,ElemType &e)
{
	LinkStNode *p;
	if(s->next == NULL)
		return false;
	p = s->next;
	e = p->data;
	s->next = p->next;
	delete p;
	return true;
}

bool GetTop(LinkStNode *s,ElemType &e)
{
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}

bool Match(char str[],int n)                       //应用：匹配圆括号。
{
	int i=0;char e;
	LinkStNode *s;
	InitStack(s);
	bool match = true;
	while(i<n && match)
	{
		if(str[i] == '(')
			Push(s,str[i]);
		else
		{
			if(str[i] == ')')
			{
				if(GetTop(s,e))
				{
					if(e != '(')
						match = false;
					else
						Pop(s,e);
				}
				else
					match = false;
			}
		}
		++i;
	}
	if(!StackEmpty(s))
		match = false;
	DestroyStack(s);
	return match;
}


int main()
{
	LinkStNode *s;
	int choice;
	ElemType e;
	do
	{
		cout << "\n菜单\n" ;
		cout << "1.初始化栈" << endl;
		cout << "2.判断栈是否为空" << endl;
		cout << "3.进栈" << endl;
		cout << "4.出栈" << endl;
		cout << "5.取栈顶元素" << endl;
		cout << "6.测试圆括号匹配功能" << endl;
		cout << "0.退出" << endl;
		cin >> choice;
		switch(choice)
		{
		case 1:
			InitStack(s);
			cout << "初始化成功！" << endl;
			break;
		case 2:
			cout << boolalpha << StackEmpty(s) << endl;
			break;
		case 3:
			cout << "请输入进栈元素：" ;
			cin >> e;
			if(Push(s,e))
				cout << "进栈成功！" << endl;
			else 
				cout << "无法进栈！" << endl;
			break;
		case 4:
			if(Pop(s,e)) cout << "出栈成功！出栈元素为：" << e << endl;
			else cout << "栈为空！" << endl;
			break;
		case 5:
			if(GetTop(s,e)) cout << "栈顶元素为：" << e << endl;
			else cout << "栈为空！" << endl;
			break;
		case 6:
			{
				string str;
				cout << "输入括号字符串（仅限输入‘（’和‘）’）:";
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区
				cin >> str;
				if (Match(const_cast<char*>(str.c_str()), str.size()))
					cout << "圆括号匹配成功！" << endl;
				else
					cout << "该系列圆括号不匹配！" << endl;
				break;
			}
		case 0:
			DestroyStack(s);
			cout << "已退出！" << endl;
			break;
		default:
			cout << "输入无效，请重新输入！" << endl;
		}
	}while(choice != 0);
}
