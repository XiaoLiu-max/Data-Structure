#include<iostream>
#include<string>
using namespace std;
#define Maxsize 50
typedef char Elemtype;

typedef struct node
{
	Elemtype data;
	node *lchild;
	node *rchild;
}BTNode;



void CreateBTree(BTNode *&b,char *str)
{
	BTNode *St[Maxsize],*p;
	int j=0,top=-1,k;
	char ch = str[j];
	b = NULL;
	while(ch != '\0')
	{
		switch(ch)
		{
		case '(':
			top++;
			k = 1;
			St[top] = p;
			break;
		case ')':
			top--;
			break;
		case ',':
			k = 2;
			break;
		default:
			{
				p = new BTNode;
				p->data = ch;
				p->lchild = NULL;p->rchild = NULL;
				if(b == NULL)
					b = p;
				else
				{
					switch(k)
					{
					case 1:
						St[top]->lchild = p;break;
					case 2:
						St[top]->rchild = p;break;
					}
				}
			}
		}
		ch = str[++j];
	}
}

void DestroyBTree(BTNode *&b)
{
	if(b != NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

BTNode* FindNode(BTNode *b,Elemtype x)
{
	BTNode *p;
	if(b == NULL)
		return NULL;
	if(b->data == x)
		return b;
	p = FindNode(b->lchild,x);
	if(p != NULL)
		return p;
	return FindNode(b->rchild,x);
}

BTNode* lchildNode(BTNode *b)
{
	return b->lchild;
}
BTNode* rchildNode(BTNode *b)
{
	return b->rchild;
}

int BTHeight(BTNode *b)
{
	if(b == NULL)
		return 0;
	int l = BTHeight(b->lchild);
	int r = BTHeight(b->rchild);
	return l > r ? l+1 : r+1;
}

void DispBTree(BTNode *b)
{
	if(b != NULL)
	{
		cout << b->data;
		if(b->lchild != NULL || b->rchild != NULL)
		{
			cout << "(";
			DispBTree(b->lchild);
			if(b->rchild != NULL)
				cout << ",";
			DispBTree(b->rchild);
			cout << ")";
		}
	}
}

//先序、中序和后序遍历的递归算法
void PreOrder(BTNode *b)
{
	if(b != NULL)
	{
		cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void InOrder(BTNode *b)
{
	if(b != NULL)
	{
		InOrder(b->lchild);
		cout << b->data;
		InOrder(b->rchild);
	}
}

void PostOrder(BTNode *b)
{
	if(b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data;
	}
}

int Nodes(BTNode *b)             //结点个数
{
	if(b == NULL)
		return 0;
	return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

void DispLeaf(BTNode *b)        //打印叶子结点
{
	if(b != NULL)
	{
		if(b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->lchild);
		DispLeaf(b->rchild);
	}
}

int Level(BTNode *b,Elemtype x,int h)         //值为x的结点所在层次
{
	if(b == NULL)
		return 0;
	if(b->data == x)
		return h;
	int l = Level(b->lchild,x,h+1);
	if(l != 0)
		return l;
	return Level(b->rchild,x,h+1);
}

void Lnodenum(BTNode *b,int h,int k,int &n)    //k层结点数
{
	if(b == NULL)
		return;
	if(h == k)
		++n;
	else
	{
		if(h < k)
		{
			Lnodenum(b->lchild,h+1,k,n);
			Lnodenum(b->rchild,h+1,k,n);
		}
	}
}

bool Like(BTNode *b1,BTNode *b2)    //判断两颗二叉树是否相似
{
	if(b1 == NULL && b2 == NULL)
		return true;
	if(b1 == NULL || b2 == NULL)
		return false;
	bool like1 = Like(b1->lchild,b2->lchild);
	bool like2 = Like(b1->rchild,b2->rchild);
	return like1 && like2;
}

bool ancestor(BTNode *b,Elemtype x)    //值为x的结点的所有祖先
{
	if(b == NULL)
		return false;
	if(b->lchild!=NULL && b->lchild->data==x || b->rchild!=NULL && b->rchild->data==x)
	{
		cout << b->data;
		return true;
	}
	if(ancestor(b->lchild,x) || ancestor(b->rchild,x))
	{
		cout << b->data;
		return true;
	}
	return false;
}

//先序、中序和后序遍历的非递归算法
typedef struct
{
	BTNode *data[Maxsize];
	int top;
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

bool Push(SqStack *&s,BTNode *e)
{
	if(s->top == Maxsize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s,BTNode *&e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack *s,BTNode *&e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

void PreOrder1(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(st);
	if(b != NULL)
	{
		Push(st,b);
		while(!StackEmpty(st))
		{
			Pop(st,p);
			cout << p->data;
			if(p->rchild != NULL)
				Push(st,p->rchild);
			if(p->lchild != NULL)
				Push(st,p->lchild);
		}
		cout << endl;
	}
	DestroyStack(st);
}

void PreOrder2(BTNode *b)
{
	BTNode *p = b;
	SqStack *st;
	InitStack(st);
	while(!StackEmpty(st) || p != NULL)
	{
		while(p != NULL)
		{
			cout << p->data;
			Push(st,p);
			p = p->lchild;
		}
		if(!StackEmpty(st))
		{
			Pop(st,p);
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

void InOrder1(BTNode *b)
{
	BTNode *p = b;
	SqStack *st;
	InitStack(st);
	while(!StackEmpty(st) || p != NULL)
	{
		while(p != NULL)
		{
			Push(st,p);
			p = p->lchild;
		}
		if(!StackEmpty(st))
		{
			Pop(st,p);
			cout << p->data;
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

void PostOrder1(BTNode *b)
{
	BTNode *p = b,*r;
	SqStack *st;
	InitStack(st);
	bool flag;
	do
	{
		while(p != NULL)
		{
			Push(st,p);
			p = p->lchild;
		}
		r = NULL;
		flag = true;
		while(!StackEmpty(st) && flag)
		{
			GetTop(st,p);
			if(p->rchild == r)
			{
				cout << p->data;
				Pop(st,p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	}while(!StackEmpty(st));
	cout << endl;
	DestroyStack(st);
}

//采用后序遍历输出从根结点到每个叶子结点的路径逆序列
void AllPath1(BTNode *b)
{
	BTNode *p = b,*r;
	SqStack *st;
	InitStack(st);
	bool flag;
	do
	{
		while(p != NULL)
		{
			Push(st,p);
			p = p->lchild;
		}
		r = NULL;
		flag = true;
		while(!StackEmpty(st) && flag)
		{
			GetTop(st,p);
			if(p->rchild == r)
			{
				if(p->lchild == NULL && p->rchild == NULL)
				{
					for(int i=st->top;i>0;--i)
						cout << st->data[i]->data;
					cout << st->data[0]->data << endl;
				}
				Pop(st,p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	}while(!StackEmpty(st));
	cout << endl;
	DestroyStack(st);
}

//层次遍历
typedef struct
{
	BTNode *data[Maxsize];
	int front,rear;
}SqQueue;

void InitQueue(SqQueue *&q)
{
	q = new SqQueue;
	q->front = q->rear = -1;
}

void DestroyQueue(SqQueue *&q)
{
	delete q;
}

bool QueueEmpty(SqQueue *q)
{
	return q->front == q->rear;
}

bool enQueue(SqQueue *&q,BTNode *e)
{
	if(q->rear == Maxsize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q,BTNode *&e)
{
	if(QueueEmpty(q))
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

void LevelOrder(BTNode *b)
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);
	enQueue(qu,b);
	while(!QueueEmpty(qu))
	{
		deQueue(qu,p);
		cout << p->data;
		if(p->lchild != NULL)
			enQueue(qu,p->lchild);
		if(p->rchild != NULL)
			enQueue(qu,p->rchild);
	}
	DestroyQueue(qu);
}

int main()
{
	BTNode *b;
	string s;
	cout << "请输入树的元素：" ;
	getline(cin,s);
	CreateBTree(b,const_cast<char*>(s.c_str()));
	cout << "打印树：" ;
	DispBTree(b);
	cout << endl;
	cout << "先序遍历：";
	PreOrder(b);cout << endl;
	PreOrder1(b);PreOrder2(b);
	cout << "中序遍历：";
	InOrder(b);cout << endl;
	InOrder1(b);
	cout << "后序遍历：";
	PostOrder(b);cout << endl;
	PostOrder1(b);
	cout << "层次遍历：";
	LevelOrder(b);
}
