#include <iostream>
#include "AdjacencyMatrix.h"
using namespace std;

//图的初始化
void AdjMatrixGraph::InitGraph()
{
	myGraph.numEdge = 0;
	myGraph.numVertex = 0;
	for (int i = 0; i<numVertices; i++)
		myGraph.vertex[i] = '$';
	for (int i = 0; i < numVertices; i++)
		for (int j = 0; j < numVertices; j++)
			myGraph.edge[i][j] = 0;
}
//有向图邻接矩阵形式的的建立
void AdjMatrixGraph::CreatAdjacencyMatrix(char pVer[], edge pEdge[])
{
	int i = 0;
	int j = 0;
	while (pVer[i] != '$')
	{
		myGraph.vertex[i] = pVer[i];
		i++;
	}
	while (pEdge[j].x != -1 && pEdge[j].y != -1)
	{
		myGraph.edge[pEdge[j].x][pEdge[j].y] = 1;
		j++;
	}

	myGraph.numVertex = i;
	myGraph.numEdge = j;

	return;

}

//有向图邻接矩阵的显示
void AdjMatrixGraph::DisplayGraph()
{
	int i;
	int j;
	printf("\n邻接矩阵： \n");
	cout << "   ";
	for (i = 0; i < myGraph.numVertex; i++)
		printf("%c ", myGraph.vertex[i]);
	cout << endl;
	for (i = 0; i < myGraph.numVertex; i++)
	{
		printf("%c  ", myGraph.vertex[i]);
		for (j = 0; j < myGraph.numVertex; j++)
		{
			printf("%d ", myGraph.edge[i][j]);
		}
		printf("\n");
	}
}

int countMatrix;                 //全局变量，搜索序列编号使用

								 //深度递归搜索主函数（森林的搜索）
void AdjMatrixGraph::DFSTraverse()
{
	int i;
	countMatrix = 0;
	for (i = 0; i < myGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myGraph.numVertex; i++)
	{
		if (!visited[i])
			DFSAdjMatrix(i);
	}

}

//深度递归搜索某顶点
void AdjMatrixGraph::DFSAdjMatrix(int i)
{
	int j;
	visit(i);                       //访问该顶点
	visited[i] = true;
	dfn[i] = countMatrix++;

	for (j = 0; j < myGraph.numVertex; j++)
	{
		if ((myGraph.edge[i][j] == 1) && !visited[j])
			DFSAdjMatrix(j);
	}
}

//访问函数
void AdjMatrixGraph::visit(int i)
{
	printf("%c ", myGraph.vertex[i]);
}


//非递归深度搜索图的邻接矩阵存储形式
//没有生成深搜序列
void AdjMatrixGraph::NonRecDFSTraverse()
{
	int i;
	for (i = 0; i < myGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myGraph.numVertex; i++)               //搜索包括不联通部分
	{
		if (!visited[i])
			NonRecDFSAdjMatrix(i);
	}

}

//非递归深搜
void AdjMatrixGraph::NonRecDFSAdjMatrix(int index)
{
	stack<int>S;
	int j;
	visit(index);
	visited[index] = true;                       //访问该节点，并将之压栈
	S.push(index);

	while (!S.empty())
	{
		index = S.top();                         //访问与该节点邻接的顶点
		for (j = 0; j < myGraph.numVertex; j++)
		{
			if (myGraph.edge[index][j] == 1 && !visited[j])     //若有未访问邻接点顶点，则访问后压栈
			{
				visit(j);
				visited[j] = true;
				S.push(j);
				break;
			}
		}
		if (j == myGraph.numVertex)                                //若无未访问邻接顶点，则弹栈，访问上个顶点的下个邻接顶点
		{
			S.pop();
		}
	}
}

//广度优先搜索主函数
void AdjMatrixGraph::BFSTraverse()
{
	int i;
	countMatrix = 0;
	for (i = 0; i < myGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myGraph.numVertex; i++)
	{
		if (!visited[i])
		{
			BFSAdjMatrix(i);
		}
	}
}

//广度优先搜索（队列）
void AdjMatrixGraph::BFSAdjMatrix(int i)
{
	queue<int> Q;
	int j, k;
	visit(i);                                        //访问当前结点，并入队
	visited[i] = true;
	bfn[i] = countMatrix++;
	Q.push(i);
	while (!Q.empty())
	{
		j = Q.front();                                    //访问与当前结点邻接的其他顶点并依次入队
		Q.pop();
		for (k = 0; k < myGraph.numVertex; k++)
		{
			if (myGraph.edge[j][k] == 1 && !visited[k])
			{
				visit(k);
				visited[k] = true;
				bfn[k] = countMatrix++;
				Q.push(k);
			}
		}
	}
}