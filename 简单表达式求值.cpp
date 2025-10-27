#include<iostream>
#include<string>
using namespace std;
#define Maxsize 50

typedef char ElemType;

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

typedef struct linknode
{
	double data;
	struct linknode *next;
}LinkStNode;

void InitStack1(LinkStNode *&s)
{
	s = new LinkStNode;
	s->next = NULL;
}

void DestroyStack1(LinkStNode *&s)
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

bool StackEmpty1(LinkStNode *s)
{
	return s->next == NULL;
}

bool Push1(LinkStNode *&s,double e)
{
	LinkStNode *p;
	p = new LinkStNode;
	p->data = e;
	p->next = s->next;
	s->next = p;
	return true;
}

bool Pop1(LinkStNode *&s,double &e)
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

bool GetTop1(LinkStNode *s,double &e)
{
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}


void trans(char *exp,char postexp[])
{
	char e;
	SqStack *optr;
	InitStack(optr);
	int i=0;
	while(*exp != '\0')
	{
		switch(*exp)
		{
		case '(':
			{
				Push(optr,*exp);
				exp++;
				break;
			}
		case ')':
			{
				Pop(optr,e);
				while(e != '(')
				{
					postexp[i++] = e;
					Pop(optr,e);
				}
				exp++;
				break;
			}
		case '-':
		case '+':
			{
				while(!StackEmpty(optr))
				{
					GetTop(optr,e);
					if(e != '(')
					{
						postexp[i++] = e;
						Pop(optr,e);
					}
					else
						break;
				}
				Push(optr,*exp);
				exp++;
				break;
			}
		case '/':
		case '*':
			{
				GetTop(optr,e);
				while(!StackEmpty(optr))
				{
					if(e == '/' || e == '*')
					{
						postexp[i++] = e;
						Pop(optr,e);
					}
					else
						break;
				}
				Push(optr,*exp);
				exp++;
				break;
			}
		default:
			{
				while(*exp>='0' && *exp<='9')
				{
					postexp[i++] = *exp;
					exp++;
				}
				postexp[i++] = '#';
			}
		}
	}
	while(!StackEmpty(optr))
	{
		Pop(optr,e);
		postexp[i++] = e;
	}
	postexp[i] = '\0';
	DestroyStack(optr);
}

double compvalue(char *postexp)
{
	double a,b,c,d,e;
	LinkStNode *opnd;
	InitStack1(opnd);
	while(*postexp !='\0')
	{
		switch(*postexp)
		{
		case '+':
			{
				Pop1(opnd,a);
				Pop1(opnd,b);
				c = b + a;
				Push1(opnd,c);
				postexp++;
				break;
			}
		case '-':
			{
				Pop1(opnd,a);
				Pop1(opnd,b);
				c = b - a;
				Push1(opnd,c);
				postexp++;
				break;
			}
		case '*':
			{
				Pop1(opnd,a);
				Pop1(opnd,b);
				c = b * a;
				Push1(opnd,c);
				postexp++;
				break;
			}
		case '/':
			{
				GetTop1(opnd,e);
				if(e)
				{
					Pop1(opnd,a);
					Pop1(opnd,b);
					c = b / a;
					Push1(opnd,c);
					postexp++;
				}
				else 
				{
					cout << "除0错误！" << endl;
					exit(0);
				}
				break;
			}
		default:
			{
				d = 0;
				while(*postexp>='0' && *postexp<='9')
				{
					d = d * 10 + *postexp - '0';
					postexp++;
				}
				Push1(opnd,d);
				postexp++;
			}
		}
	}
	GetTop1(opnd,e);
	DestroyStack1(opnd);
	return e;
}

int main()
{
	string str;
	getline(cin,str);
	char postexp[Maxsize];
	trans(const_cast<char*>(str.c_str()),postexp);
	cout << "中缀表达式为：" << str << endl;
	cout << "后缀表达式为：" << postexp << endl;
	cout << "表达式的值：" << compvalue(postexp) << endl;
}
