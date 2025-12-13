#include<iostream>
#define MAXV 50
#define Maxsize 50
#define INF 32767
using namespace std;

typedef int InfoType;

typedef struct ANode
{
	int adjvex;
	ANode* nextarc;
	int weight;
}ArcNode;

typedef struct Vnode
{
	InfoType data;
	ArcNode* firstarc;
}VNode;

typedef struct
{
	VNode adjlist[MAXV];
	int n,e;
}AdjGraph;

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

void TopSort(AdjGraph *G)
{
	SqStack *st;
	InitStack(st);
	int count = 0;
	int indegree[MAXV];
	for(int i=0;i<G->n;++i) indegree[i] = 0;
	for(int i=0;i<G->n;++i)
	{
		ArcNode *p = G->adjlist[i].firstarc;
		while(p != NULL)
		{
			int w = p->adjvex;
			indegree[w]++;
			p = p->nextarc;
		}
	}
	for(int i=0;i<G->n;++i)
		if(indegree[i] == 0)
			Push(st,i);
	int e;
	while(!StackEmpty(st))
	{
		Pop(st,e);
		cout << e << " ";
		count++;
		ArcNode *q = G->adjlist[e].firstarc;
		while(q != NULL)
		{
			int w = q->adjvex;
			indegree[w]--;
			if(indegree[w] == 0)
				Push(st,w);
			q = q->nextarc;
		}
	}
	cout << endl;
	if(count < G->n)
		cout << "该图存在回路!" << endl;
	DestroyStack(st);
}

void Greatadj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e)
{
	G = new AdjGraph;
	for(int i=0;i<n;++i)
		G->adjlist[i].firstarc = NULL;
	for(int i=0;i<n;++i)
	{
		for(int j=n-1;j>=0;--j)
		{
			if(A[i][j] != 0 && A[i][j] != INF)
			{
				ArcNode *p = new ArcNode;
				p->adjvex = j;
				p->weight = A[i][j];
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n;
	G->e = e;
}

void DestroyAdj(AdjGraph *&G)
{
	ArcNode *pre,*p;
	for(int i=0;i<G->n;++i)
	{
		pre = G->adjlist[i].firstarc;
		if(pre != NULL)
		{
			p = pre->nextarc;
			while(p != NULL)
			{
				delete pre;
				pre = p;
				p = p->nextarc;
			}
			delete pre;
		}
	}
	delete G;
}


int main()
{
	AdjGraph *G;
	int n,e;
	cout << "请输入有向图的结点树和边数：" ;
	cin >> n >> e;
	cout << "请输入该图的邻接矩阵:" << endl;
	int A[MAXV][MAXV];
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
			cin >> A[i][j];
	}
	Greatadj(G,A,n,e);
	cout << "有向图的拓扑排序结果：" << endl;
	TopSort(G);
	DestroyAdj(G);	
}
