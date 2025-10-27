#include<iostream>
using namespace std;

typedef struct snode
{
	char data;
	snode *next;
}LinkStrNode;

void InitStrList(LinkStrNode *&L)
{
	L = new LinkStrNode;
	L->next = NULL;
}

void StrAssign(LinkStrNode *&L,const char* str)
{
	int i=0;
	L = new LinkStrNode;
	LinkStrNode *s,*r;
	r = L;
	while(str[i] != '\0')
	{
		s = new LinkStrNode;
		s->data = str[i];
		r->next = s;
		r = s;
		++i;
	}
	r->next = NULL;
}

void Destroy(LinkStrNode *&L)
{
	LinkStrNode *pre = L,*p = pre->next;
	while(p != NULL)
	{
		delete pre;
		pre = p;
		p = p->next;
	}
	delete pre;
}

void Strcpy(LinkStrNode *&L,LinkStrNode *t)
{
	Destroy(L);
	InitStrList(L);
	LinkStrNode *p = t->next;
	LinkStrNode *r = L;
	while(p != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
}

int Strlength(LinkStrNode *s)
{
	LinkStrNode *p = s->next;
	int len = 0;
	while(p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

bool StrEqual(LinkStrNode *s,LinkStrNode *t)
{
	LinkStrNode *p = s->next;
	LinkStrNode *q = t->next;
	while(p != NULL && q != NULL && p->data == q->data)
	{
		p = p->next;
		q = q->next;
	}
	return p==NULL && q==NULL;
}

LinkStrNode* Concat(LinkStrNode *s,LinkStrNode *t)
{
	LinkStrNode *newstr;
	InitStrList(newstr);
	LinkStrNode *p = s->next;
	LinkStrNode *r = newstr;
	while(p != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	p = t->next;
	while(p != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return newstr;
}

//求子串
LinkStrNode* SubStr(LinkStrNode *s,int i,int j)
{
	LinkStrNode *str;
	InitStrList(str);
	LinkStrNode *p = s->next;
	LinkStrNode *r = str;
	if(i<=0 || i>Strlength(s) || j<0 || i+j-1 > Strlength(s))
		return str;
	for(int k=1;k<i;++k)                          //注意k从1开始
		p = p->next;
	for(int k=0;k<j;++k)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

//子串插入
LinkStrNode* InsStr(LinkStrNode *s1,int i,LinkStrNode *s2)
{
	LinkStrNode *str = new LinkStrNode;
	InitStrList(str);
	LinkStrNode *p1 = s1->next,*p2 = s2->next,*r = str;
	for(int k=0;k<i-1&&p1!=NULL;++k)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	while(p2 != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p2->data;
		r->next = q;
		r = q;
		p2 = p2->next;
	}
	while(p1 != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode* DelStr(LinkStrNode *s,int i,int j)
{
	LinkStrNode *str = new LinkStrNode;
	InitStrList(str);
	LinkStrNode *p = s->next;
	LinkStrNode *r = str;
	if(i<=0 || i>Strlength(s) || j<0 || i+j-1 > Strlength(s))
		return str;
	for(int k=0;k<i-1&&p!=NULL;++k)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	for(int k=0;k<j&&p!=NULL;++k)
		p = p->next;
	while(p != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode* RepStr(LinkStrNode *s,int i,int j,LinkStrNode *t)
{
	LinkStrNode *str = new LinkStrNode;
	InitStrList(str);
	LinkStrNode *p1 = s->next,*p2 = t->next,*r = str;
	if(i<=0 || i>Strlength(s) || j<0 || i+j-1 > Strlength(s))
		return str;
	for(int k=0;k<i-1&&p1!=NULL;++k)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	for(int k=0;k<j&&p1!=NULL;++k)
		p1 = p1->next;
	while(p2 != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p2->data;
		r->next = q;
		r = q;
		p2 = p2->next;
	}
	while(p1 != NULL)
	{
		LinkStrNode *q = new LinkStrNode;
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	r->next = NULL;
	return str;
}

void DispStr(LinkStrNode *s)
{
	LinkStrNode *p = s->next;
	while(p != NULL)
	{
		cout << p->data;
		p = p->next;
	}
	cout << endl;
}

int main()
{
	LinkStrNode *s;
	InitStrList(s);
	StrAssign(s,"abc");
	DispStr(s);
	DispStr(SubStr(s,1,2));
}
