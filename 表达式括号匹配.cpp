#include<iostream>
#include<string>
#include<cstring>
#include<vector>
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

bool Match(vector<char>& str,int n)
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
	vector<char> arr;
	char c;
	cin >> c;
	while(c != '@')
	{
		arr.push_back(c);
		cin >> c;
	}
	if(Match(arr,arr.size()))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
