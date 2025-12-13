#include<iostream>
#define MAXV 50
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

int visited[MAXV] = {0};


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
			cout << p->adjvex << " " << "→" << " ";
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


//顶点u→v是否存在简单路径
bool ExistPath(AdjGraph *G,int u,int v)
{
	ArcNode *p = G->adjlist[u].firstarc;
	visited[u] = 1;
	if(u == v) return true;
	while(p != NULL)
	{
		int w = p->adjvex;
		if(visited[w] == 0)
		{
			if(ExistPath(G,w,v))
				return true;
		}
		p = p->nextarc;
	}
	return false;
}

//输出一条u→v的简单路径
void FindaPath(AdjGraph *G,int u,int v,int path[],int d) //d初始值为-1
{
	ArcNode *p = G->adjlist[u].firstarc;
	visited[u] = 1;
	d++;path[d] = u;
	if(u == v)
	{
		for(int i=0;i<=d;++i)
			cout << path[i] << " ";
		cout << endl;
		return;
	}
	while(p != NULL)
	{
		int w = p->adjvex;
		if(visited[w] == 0)
			FindaPath(G,w,v,path,d);
		p = p->nextarc;
	}
}

//u→v的所有简单路径
void FindAllPath(AdjGraph *G,int u,int v,int path[],int d)
{
	ArcNode *p = G->adjlist[u].firstarc;
	visited[u] = 1;
	d++;path[d] = u;
	if(u == v)
	{
		for(int i=0;i<=d;++i)
			cout << path[i] << " ";
		cout << endl;
		visited[u] = 0;
		return;
	}
	while(p != NULL)
	{
		int w = p->adjvex;
		if(visited[w] == 0)
			FindAllPath(G,w,v,path,d);
		p = p->nextarc;
	}
	visited[u] = 0;
}

//u→v长度为l的所有简单路径
void PathlenAll(AdjGraph *G,int u,int v,int l,int path[],int d)
{
	ArcNode *p = G->adjlist[u].firstarc;
	visited[u] = 1;
	d++;path[d] = u;
	if(u == v && d == l)
	{
		for(int i=0;i<=d;++i)
			cout << path[i] << " ";
		cout << endl;
		visited[u] = 0;
		return;
	}
	while(p != NULL)
	{
		int w = p->adjvex;
		if(visited[w] == 0)
			PathlenAll(G,w,v,l,path,d);
		p = p->nextarc;
	}
	visited[u] = 0;
}

void DFSPath(AdjGraph *G,int u,int v,int path[],int d)
{
	ArcNode *p = G->adjlist[u].firstarc;
	d++;path[d] = u;
	visited[u] = 1;
	while(p != NULL)
	{
		int w = p->adjvex;
		if(w == v && d > 1)
		{
			cout << " ";
			for(int i=0;i<=d;++i)
				cout << path[i] << " ";
			cout << v << endl;
		}
		if(visited[w] == 0)
			DFSPath(G,w,v,path,d);
		p = p->nextarc;
	}
	visited[u] = 0;
}
void FindCyclePath(AdjGraph *G,int k)    //输出经过k的所有回路
{
	int path[MAXV];
	DFSPath(G,k,k,path,-1);
}

int main()
{
	//测试PathlenAll的功能
//	int n,e;
//	int path[MAXV];
//	cout << "输入图G的顶点数和边数：";
//	cin >> n >> e;
//	int A[MAXV][MAXV];
//	cout << "输入邻接矩阵：" << endl;
//	for(int i=0;i<n;++i)
//		for(int j=0;j<n;++j)
//			cin >> A[i][j];
//	AdjGraph *G;
//	Createadj(G,A,n,e);
//	for(int i=0;i<n;++i)
//		visited[i] = 0;
//	cout << "图G:" << endl;
//	DispAdj(G);
//	cout << "从顶点u到顶点v的所有长度为l的路径，输入u,v,l:";
//	int u,v,l;
//	cin >> u >> v >> l;
//	PathlenAll(G,u,v,l,path,-1);
//	cout << endl;
//	DestroyAdj(G);
	
	//测试DFSPath的功能
	int n,e;
	cout << "输入图G的顶点数和边数：";
	cin >> n >> e;
	int A[MAXV][MAXV];
	cout << "输入邻接矩阵：" << endl;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin >> A[i][j];
	AdjGraph *G;
	Createadj(G,A,n,e);
	for(int i=0;i<n;++i)
		visited[i] = 0;
	cout << "图G:" << endl;
	DispAdj(G);
	int k;
	cout << "图G中经过顶点k的所有回路，输入k:";
	cin >> k;
	FindCyclePath(G,k);
	cout << endl;
	DestroyAdj(G);
}
