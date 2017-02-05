#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
#define  NumVertices 100

                                  //�ڽӾ���

typedef string  VertexData;         //����
typedef int     EdgeData;           //��
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

void CreateMTGragh(MTGraph *G)                            //����ͼ���ڽӾ���
{
	int i, j, k;
	EdgeData w;
	VertexData vexi, vexj;
	ifstream in("G.txt");
	in >> G->numVertex >> G->numEdge;                       //���붥�����ͱ���

	for (i = 0; i < G->numVertex; i++)                      //���������
		in >> G->vertex[i];

	for (i = 0; i < G->numVertex; i++)
		for (j = 0; j<G->numVertex; j++)
			G->edge[i][j] = 0;                               //�ڽӾ����ʼ��
	for (k = 0; k<G->numEdge; k++) 
	{                                                         //�����ڽӾ���
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
	for (k = 0; k<g.numVertex; k++)                               //�����
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

//��ӡ·��
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
				cout << i << " To " << j <<"��  ";
				showPath(path, i, j);
				cout <<"����Ϊ��"<<dist[i][j] << endl;
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
	cout << "	1. �ڽӾ���" << endl;
	cout << "	2. ���·��" << endl;
	cout << "	3. �ɴ����" << endl;
	cout << "	4. �˳�"     << endl;

	while (1)
	{
		int op;
		cin >> op;
		if(op==1)
		{    printf("�ڽӾ���\n");
	         ShowGraph(&G);
		}
		if (op == 2)
		{
			FloydPath(G, dist, path);
			printf("���·����\n");
			PrintPath(G, dist, path);
		}
		if (op == 3)
		{
	    printf("�ɴ����\n");
	    TranClosure(dist, t, G.numVertex);
	    PrintClosure(G, t);
		}
		if (op == 4)
			break;
	}
	return 0;

}