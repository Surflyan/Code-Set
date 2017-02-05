#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

                                      //�ڽӾ���
#define  NumVertices 50
typedef string  VertexData;          //����
typedef int EdgeData;                //��

typedef struct {
	VertexData vertex[NumVertices];
	EdgeData cost[NumVertices][NumVertices];
	int n, e;
} MTGraph;

VertexData v0;
int Sit;

int LocateVex(MTGraph *G, VertexData v)
{
	int i = 0;
	for (i = 0; i < G->n; i++)
	{
		if (G->vertex[i] == v) break;
	}
	return i;
}

void CreateMTGragh(MTGraph *G)               //����ͼ���ڽӾ���
{
	int i, j, k;
	EdgeData w;
	VertexData vexi, vexj;
	ifstream in("G.txt");
	in >> G->n >> G->e; 
	for (i = 0; i < G->n; i++) 
		in >> G->vertex[i];
	for (i = 0; i < G->n; i++)
		for (j = 0; j<G->n; j++)
			G->cost[i][j] = 0; 
	for (k = 0; k<G->e; k++)
	{
		in >> vexi >> vexj >> w; 
		i = LocateVex(G, vexi); j = LocateVex(G, vexj);
		G->cost[i][j] = w;
						  	
	}
	in >> v0;
	in.close();

}

void ShowGraph(MTGraph *A)
{
	int i, j;
	for (i = 0; i < A->n; i++)
	{
		for (j = 0; j < A->n; j++)
		{
			cout << A->cost[i][j] << " ";
		}
		cout << endl;
	}
}

void DijkstraPath(MTGraph g, int *dist, int *path, int Sit)   //Sit��ʾԴ��������Ӧ�õ�int
{
	int i, j, k;
	bool *visited = new bool[g.n];;
	for (i = 0; i<g.n; i++)                        //��ʼ�� 
	{
		if (g.cost[Sit][i]>0 && i != Sit)
		{
			dist[i] = g.cost[Sit][i];
			path[i] = Sit;                   //path��¼���·���ϴ�V0��i��ǰһ������ 
		}
		else
		{
			dist[i] = INT_MAX;                     //��i����v0ֱ�����ڣ���Ȩֵ��Ϊ����� 
			path[i] = -1;
		}
		visited[i] = false;
		path[Sit] = Sit;
		dist[Sit] = 0;
	}
	visited[Sit] = true;
	for (i = 1; i<g.n; i++)  
	{
		int min = INT_MAX;
		int u = 0;
		for (j = 0; j<g.n; j++)                              //Ѱ��δ����չ��Ȩֵ��С�Ķ��� 
		{
			if (visited[j] == false && dist[j]<min)
			{
				min = dist[j];
				u = j;
			}
		}
		visited[u] = true;
		for (k = 0; k<g.n; k++)                          //����dist�����·����ֵ 
		{
			if (visited[k] == false && g.cost[u][k]>0 && min + g.cost[u][k]<dist[k])
			{
				dist[k] = min + g.cost[u][k];
				path[k] = u;
			}
		}
	}
	delete[]visited;
}

void showPath(int *path, int v, int Sit)   //��ӡ���·���ϵĸ������� 
{
	stack<int> s;
	int u = v;
	while (v != Sit)
	{
		s.push(v);
		v = path[v];
	}
	s.push(v);
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
}

int main()
{
	int i;
	MTGraph G;
	CreateMTGragh(&G);
	printf("�ڽӾ���\n");
	ShowGraph(&G);

	int *dist = new int[G.n];
	int *path = new int[G.n];
	Sit = LocateVex(&G, v0);                          
	DijkstraPath(G, dist, path, Sit);
	printf("���·����\n");
	for (i = 0; i<G.n; i++)
	{
		if (i != Sit)
		{   
			showPath(path, i, Sit);
			cout << dist[i] << endl;
		}
	}
	delete[]dist;
	delete[]path;
	getchar();
	return 0;
}
