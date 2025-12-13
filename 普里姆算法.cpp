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

void Prim(MatGraph g,int v)
{
	int closest[MAXV],lowcost[MAXV];
	int k;
	for(int i=0;i<g.n;++i)     //初始化
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for(int i=1;i<g.n;++i)    //找出n-1个结点
	{
		int mindist = INF;
		for(int j=0;j<g.n;++j)
			if(lowcost[j] != 0 && lowcost[j] < mindist)
			{
				mindist = lowcost[j];
				k = j;
			}
		lowcost[k] = 0;
		cout << "边：" << closest[k] << "→" << k << "，权为：" << mindist << endl;
		for(int j=0;j<g.n;++j)
			if(lowcost[j] != 0 && g.edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.edges[k][j];
				closest[j] = k;
			}
	}
}

int main()
{
	int n,e;
	cout << "请输入带权图的顶点数和边数：";
	cin >> n >> e;
	MatGraph g;
	g.e = e;
	g.n = n;
	cout << "请输入邻接矩阵：" << endl;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin >> g.edges[i][j];
	cout << "普利姆算法结果：" << endl;
	Prim(g,0);
}
