#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
#define  NumVertices 100

                                  //邻接矩阵

typedef string  VertexData;         //顶点
typedef int     EdgeData;           //边
VertexData v0;
int Locate_v0;

typedef struct {
	VertexData vertex[NumVertices];
	EdgeData edge[NumVertices][NumVertices];
	int numVertex, numEdge;
} MTGraph;


int LocateVex(MTGraph *G, VertexData v)
{
	int i = 0;
	for (i = 0; i < G->numVertex; i++)
	{
		if (G->vertex[i] == v) break;
	}
	return i;
}

void CreateMTGragh(MTGraph *G)                            //建立图的邻接矩阵
{
	int i, j, k;
	EdgeData w;
	VertexData vexi, vexj;
	ifstream in("G.txt");
	in >> G->numVertex >> G->numEdge;                       //输入顶点数和边数

	for (i = 0; i < G->numVertex; i++)                      //建立顶点表
		in >> G->vertex[i];

	for (i = 0; i < G->numVertex; i++)
		for (j = 0; j<G->numVertex; j++)
			G->edge[i][j] = 0;                               //邻接矩阵初始化
	for (k = 0; k<G->numEdge; k++) 
	{                                                         //建立邻接矩阵
		in >> vexi >> vexj >> w; 
		i = LocateVex(G, vexi); j = LocateVex(G, vexj);
		G->edge[i][j] = w; 
						 		
	}

	in.close();

}

void ShowGraph(MTGraph *A)
{
	int i, j;
	
	for (i = 0; i < A->numVertex; i++)
	{
		for (j = 0; j < A->numVertex; j++)
		{
			cout << A->edge[i][j] << " ";
		}
		cout << endl;
	}
}

void FloydPath(MTGraph g, int dist[NumVertices][NumVertices], int path[NumVertices][NumVertices])
{
	int i, j, k;
	for (i = 0; i<g.numVertex; i++)
		for (j = 0; j<g.numVertex; j++)
		{
			if (g.edge[i][j]>0)
			{
				dist[i][j] = g.edge[i][j];
				path[i][j] = i;
			}
			else
			{
				if (i != j)
				{
					dist[i][j] = INT_MAX;
					path[i][j] = -1;
				}
				else
				{
					dist[i][j] = 0;
					path[i][j] = i;
				}
			}
		}
	for (k = 0; k<g.numVertex; k++)                               //插入点
		for (i = 0; i<g.numVertex; i++)
			for (j = 0; j<g.numVertex; j++)
			{
				if ((dist[i][k]>0 && dist[i][k]<INT_MAX) &&
					(dist[k][j]>0 && dist[k][j]<INT_MAX) &&
					dist[i][k] + dist[k][j]<dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];                  
				}
			}
}

//打印路径
void showPath(int path[NumVertices][NumVertices], int s, int t)     
{
	stack<int> st;
	int v = t;
	while (t != s)
	{
		st.push(t);
		t = path[s][t];
	}
	st.push(t);
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}

}


void TranClosure(int dist[NumVertices][NumVertices], int t[NumVertices][NumVertices], int N)
{
	for (int i = 0; i<N; i++)                     
		for (int j = 0; j<N; j++)
		{
			if ((i == j) || (dist[i][j]) == 1)         
				t[i][j] = 1;
			else
				t[i][j] = 0;
		}

	for (int k = 0; k<N; k++)
		for (int i = 0; i<N; i++)
			for (int j = 0; j<N; j++)
				t[i][j] = t[i][j] || (t[i][k] && t[k][j]);
}
void PrintPath(MTGraph G, int dist[][NumVertices],int path[][NumVertices])
{
	for (int i = 0; i < G.numVertex; i++)
	{
		for (int j = 0; j < G.numVertex; j++)
		{
			if (dist[i][j] > 0 && dist[i][j] < INT_MAX)
			{
				cout << i << " To " << j <<"：  ";
				showPath(path, i, j);
				cout <<"长度为："<<dist[i][j] << endl;
			}
		}
	}
}
void PrintClosure(MTGraph G, int t[][NumVertices])
{
	for (int i = 0; i<G.numVertex; i++)
	{
		for (int j = 0; j<G.numVertex; j++)
			printf("%d ", t[i][j]);
		printf("\n");
	}
}
int main()
{
	MTGraph G;
	CreateMTGragh(&G);
	
	int dist[NumVertices][NumVertices];
	int path[NumVertices][NumVertices];
	int t[NumVertices][NumVertices];
	cout << "	1. 邻接矩阵" << endl;
	cout << "	2. 最短路径" << endl;
	cout << "	3. 可达矩阵" << endl;
	cout << "	4. 退出"     << endl;

	while (1)
	{
		int op;
		cin >> op;
		if(op==1)
		{    printf("邻接矩阵：\n");
	         ShowGraph(&G);
		}
		if (op == 2)
		{
			FloydPath(G, dist, path);
			printf("最短路径：\n");
			PrintPath(G, dist, path);
		}
		if (op == 3)
		{
	    printf("可达矩阵：\n");
	    TranClosure(dist, t, G.numVertex);
	    PrintClosure(G, t);
		}
		if (op == 4)
			break;
	}
	return 0;

}