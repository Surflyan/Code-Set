#include <iostream>

#include "AdjacencyList.h"
using namespace std;

//有向图的邻接表的建立
void AdjListGraph::CreatAdjListGraph(char pVer[], edge pEdge[])
{
	int i = 0;
	while (pVer[i] != '$')
	{
		myAdjGraph.vexList[i].vertex = pVer[i];
		myAdjGraph.vexList[i].firstEdge = NULL;
		i++;
	}
	myAdjGraph.numVertex = i;

	i = 0;
	while (pEdge[i].x != -1 && pEdge[i].y != -1)                   //边结构的建立
	{
		edgeNode *pNode = new edgeNode;
		pNode->adjvex = pEdge[i].y;                                 //边的相同头顶点，不同尾顶点
		pNode->next = myAdjGraph.vexList[pEdge[i].x].firstEdge;
		myAdjGraph.vexList[pEdge[i].x].firstEdge = pNode;
		i++;
	}
	myAdjGraph.numEdge = i;

}

//释放邻接表
void AdjListGraph::DestroyAdjList()
{
	int i = 0;
	edgeNode* pNode;
	while (i < myAdjGraph.numVertex)
	{
		if (myAdjGraph.vexList[i].firstEdge == NULL)
		{
			i++;
			continue;
		}
		while (myAdjGraph.vexList[i].firstEdge->next != NULL)
		{
			pNode = myAdjGraph.vexList[i].firstEdge->next;
			delete myAdjGraph.vexList[i].firstEdge;
			myAdjGraph.vexList[i].firstEdge = pNode;
		}
		delete myAdjGraph.vexList[i].firstEdge;
		i++;

	}
}

//输出邻接表表示的图，输出顶点（非下标)
void AdjListGraph::DisplayGraph()
{
	int i = 0;
	printf("\n邻接表 ：\n");
	while (i < myAdjGraph.numVertex)
	{
		printf("顶点 %c: ", myAdjGraph.vexList[i].vertex);
		edgeNode *p = NULL;
		p = myAdjGraph.vexList[i].firstEdge;
		while (p != NULL)
		{
			printf("%c ", myAdjGraph.vexList[p->adjvex].vertex);
			p = p->next;
		}
		i++;
		printf("\n");

	}
}

void AdjListGraph::visit(int i)
{
	printf("%c ", myAdjGraph.vexList[i].vertex);
}

int countList;           //全局变量，给DFS序列编号

						 //深度优先遍历主算法
void AdjListGraph::DFSAdjListTraverse()
{
	int i;
	countList = 0;
	for (i = 0; i < myAdjGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myAdjGraph.numVertex; i++)
	{
		if (!visited[i])
			DFSAdjList(i);
	}
}
//从一个定点出发的深度优先遍历算法；
//以Vi为出发点对邻接表表示的图进行先深搜索
void AdjListGraph::DFSAdjList(int i)
{
	edgeNode *pNode;
	visit(i);
	visited[i] = true;
	dfn[i] = countList++;
	pNode = myAdjGraph.vexList[i].firstEdge;
	while (pNode != NULL)
	{
		if (!visited[pNode->adjvex])
			DFSAdjList(pNode->adjvex);
		pNode = pNode->next;
	}
}

////非递归深度搜索邻接表主函数（森林的搜索）
void AdjListGraph::NonRecDFSListTraverse()
{
	int i;
	countList = 0;
	for (i = 0; i < myAdjGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myAdjGraph.numVertex; i++)
	{
		if (!visited[i])
			NonRecDFSList(i);
	}
}

//非递归深度优先搜索
void AdjListGraph::NonRecDFSList(int i)
{
	stack<int> S;
	edgeNode *pNode;
	visit(i);
	visited[i] = true;                                   //访问当前顶点，并压栈
	S.push(i);

	while (!S.empty())
	{
		i = S.top();
		pNode = myAdjGraph.vexList[i].firstEdge;
		while (pNode != NULL)                     //若栈顶顶点没有邻接顶点，弹栈
		{
			if (!visited[pNode->adjvex])                //访问栈顶顶点未访问邻接顶点，并压栈
			{
				visit(pNode->adjvex);
				visited[pNode->adjvex] = true;
				S.push(pNode->adjvex);
				break;
			}
			pNode = pNode->next;
		}
		if (pNode == NULL)                  //只有当某一顶点的所有邻接访问完之后，pop
			S.pop();
	}
}

//广度优先搜索主函数
void AdjListGraph::BFSAdjListTraverse()
{
	int i;
	countList = 0;
	for (i = 0; i < myAdjGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myAdjGraph.numVertex; i++)
	{
		if (!visited[i])
			BFSAdjList(i);
	}
	printf("\n");
}

//广度优先搜索
void AdjListGraph::BFSAdjList(int i)
{
	int j;
	queue<int> Q;                       //访问当前顶点并入队
	edgeNode *pNode;
	visit(i);
	visited[i] = true;
	bfn[i] = countList++;
	while (!Q.empty())
	{
		j = Q.front();
		Q.pop();
		pNode = myAdjGraph.vexList[i].firstEdge;           //访问队首顶点的所有邻接顶点，并依次入队
		while (pNode != NULL)
		{
			if (!visited[pNode->adjvex])
			{
				visit(pNode->adjvex);
				visited[pNode->adjvex] = true;
				bfn[pNode->adjvex] = countList++;
				Q.push(pNode->adjvex);
			}
			pNode = pNode->next;
		}
	}

}