#include<iostream>
#define MAXV 50
#define INF 32767
using namespace std;

typedef int InfoType;

typedef struct
{
	int no;
	InfoType info;
}VertexType;

typedef struct
{
	int edges[MAXV][MAXV];
	int n,e;
	VertexType vexs[MAXV];
}MatGraph;

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

void MatToList(MatGraph g,AdjGraph *&G)           //带权图邻接矩阵转为邻接表
{
	ArcNode *p;
	G = new AdjGraph;
	for(int i=0;i<g.n;++i)
		G->adjlist[i].firstarc = NULL;
	for(int i=0;i<g.n;++i)
	{
		for(int j=g.n-1;j>=0;--j)
		{
			if(g.edges[i][j]!=0 && g.edges[i][j]!=INF)
			{
				p = new ArcNode;
				p->adjvex = j;
				p->weight = g.edges[i][j];
				p->nextarc =G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = g.n;
	G->e = g.e;
}
void ListToMat(AdjGraph *G,MatGraph &g)            //带权图邻接表转为邻接矩阵
{
	ArcNode *p;
	for(int i=0;i<G->n;++i)
	{
		p = G->adjlist[i].firstarc;
		while(p != NULL)
		{
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n;
	g.e = G->e;
}

//图的遍历


int visited[MAXV] = {0};
void DFS(AdjGraph *G,int v)          //深度优先遍历
{
	ArcNode *p;
	visited[v] = 1;
	cout << v;
	p = G->adjlist[v].firstarc;
	while(p != NULL)
	{
		if(visited[p->adjvex] == 0)
			DFS(G,p->adjvex);
		p = p->nextarc;
	}
}

#define Maxsize 50

typedef int ElemType;

//顺序队
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

int Visited[MAXV];
void BFS(AdjGraph *G,int v)         //广度优先遍历
{
	ArcNode *p;int w;
	SqQueue *q;
	InitQueue(q);
	for(int i=0;i<G->n;++i)
		Visited[i] = 0;
	Visited[v] = 1;
	cout << v << " ";
	enQueue(q,v);
	while(!QueueEmpty(q))
	{
		deQueue(q,w);
		p = G->adjlist[w].firstarc;
		while(p != NULL)
		{
			if(Visited[p->adjvex] == 0)
			{
				cout << p->adjvex << " ";
				Visited[p->adjvex] = 1;
				enQueue(q,p->adjvex);
			}
			p = p->nextarc;
		}
	}
	cout << endl;
}

//非连通图的遍历
void DFS1(AdjGraph *G)
{
	for(int i=0;i<G->n;++i)
		if(visited[i] == 0)
			DFS(G,i);
}
void BFS1(AdjGraph *G)
{
	for(int i=0;i<G->n;++i)
	{
		if(Visited[i] == 0)
			BFS(G,i);
	}
}
bool Connect(AdjGraph *G)         //判断是否为连通图
{
	bool flag = true;
	for(int i=0;i<G->n;++i)
		visited[i] = 0;
	DFS(G,0);
	for(int i=0;i<G->n;++i)
	{
		if(visited[i] == 0)
		{
			flag = false;
			break;
		}
	}
	return flag;
}

int main()
{
	int n,e;
	cout << "请依次输入结点和边的个数：";
	cin >> n >> e;
	int A[MAXV][MAXV];
	cout << "请输入邻接矩阵：" << endl;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<n;++j)
			cin >> A[i][j];
	}
	AdjGraph *G;
	Createadj(G,A,n,e);
	cout << "打印邻接表：" << endl;
	DispAdj(G);
	cout << endl;
	cout << boolalpha << Connect(G) << endl;
}
