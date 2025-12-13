#include<iostream>
#define MAXV 50
#define INF 32767
#define Maxsize 50
using namespace std;

typedef struct
{
	int v;
	int dist;
}QUEUE1;
typedef struct
{
	int v;
}QUEUE2;
typedef QUEUE2 ElemType;
typedef int InfoType;

typedef struct{
	ElemType data[Maxsize];
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

bool enQueue(SqQueue *&q,ElemType e)
{
	if(q->rear == Maxsize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q,ElemType &e)
{
	if(QueueEmpty(q))
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

int Count(SqQueue *q)
{
	return q->rear - q->front;
}


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

void Createadj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e)
{
	G = new AdjGraph;
	for(int i=0;i<n;++i)
		G->adjlist[i].firstarc = NULL;
	ArcNode *p;
	for(int i=0;i<n;++i)
	{
		for(int j=n-1;j>=0;--j)
		{
			if(A[i][j] != 0 && A[i][j] != INF)
			{
				p = new ArcNode;
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
void DispAdj(AdjGraph *G)
{
	ArcNode* p;
	for(int i=0;i<G->n;++i)
	{
		p = G->adjlist[i].firstarc;
		cout << i << ":" << " ";
		while(p != NULL)
		{
			cout << p->adjvex << p->weight << "→";
			p = p->nextarc;
		}
		cout << "^" << endl;
	}
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

//u到v最短路径长度（不带权图）
//int shortpathlen(AdjGraph *G,int u,int v)       //解法一
//{
//	ArcNode *p;
//	SqQueue *qu;
//	InitQueue(qu);
//	int visited[MAXV];
//	for(int i=0;i<G->n;++i)
//		visited[i] = 0;
//	QUEUE1 e,e1;
//	e.dist = 0;
//	e.v = u;
//	enQueue(qu,e);
//	visited[u] = 1;
//	while(!QueueEmpty(qu))
//	{
//		deQueue(qu,e);
//		u = e.v;
//		if(u == v) return e.dist;
//		p = G->adjlist[u].firstarc;
//		while(p != NULL)
//		{
//			int w = p->adjvex;
//			if(visited[w] == 0)
//			{
//				e1.dist = e.dist + 1;
//				e1.v = w;
//				visited[w] = 1;
//				enQueue(qu,e1);
//			}
//			p = p->nextarc;
//		}
//	}
//	DestroyQueue(qu);
//}

int shortpathlen(AdjGraph *G,int u,int v)
{
	ArcNode *p;
	SqQueue *q;
	InitQueue(q);
	int visited[MAXV];
	for(int i=0;i<G->n;++i)
		visited[i] = 0;
	QUEUE2 e,e1;
	e.v = u;
	enQueue(q,e);
	visited[u] = 1;
	int ans = 0;
	while(!QueueEmpty(q))
	{
		int cnt = Count(q);
		for(int i=0;i<cnt;++i)
		{
			deQueue(q,e);
			u = e.v;
			if(u == v)
				return ans;
			p = G->adjlist[u].firstarc;
			while(p != NULL)
			{
				int w = p->adjvex;
				if(visited[w] == 0)
				{
					e1.v = w;
					enQueue(q,e1);
					visited[w] = 1;
				}
				p = p->nextarc;
			}
		}
		ans++;
	}
	DestroyQueue(q);
}

int main()
{
	int n,e;
	cout << "请输入不带权图的顶点数和边数：";
	cin >> n >> e;
	cout << "请输入邻接矩阵：" << endl;
	int A[MAXV][MAXV];
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin >> A[i][j];
	AdjGraph *G;
	Createadj(G,A,n,e);
	cout << "求u到v的最短路径，请输入u、v:";
	int u,v;
	cin >> u >> v;
	cout << "最短路径为：" << shortpathlen(G,u,v);
}
