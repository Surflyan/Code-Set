#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "OrthogonalList.h"

using namespace std;

//从文件读取图的信息，提取顶点存在verArray数组中
//数组最后设为‘$’标志，返回顶点的数目，
int FindVertices(char verArray[], int numVer)
{
	FILE *fp;
	char a, b;
	int i = 0;
	int j = 0;

	if ((fp = fopen("Graph.txt", "r")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(1);
	}
	int index = 0;
	while (!feof(fp))
	{
		int flag = 1;
		int i = 0;
		int j = 0;
		fscanf(fp, "(%c,%c)", &a, &b);
		while (i< numVer)
		{
			if (verArray[i++] == a)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			verArray[index++] = a;
		}

		flag = 1;
		while (j <= index)
		{
			if (verArray[j++] == b)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			verArray[index++] = b;
		}

	}
	verArray[index] = '$';
	fclose(fp);
	return index;

}

//从文件读取图的信息，提取边存在edgeArray数组中
//数组最后设为（0，0），返回边的数目
int FindEdge(char verArray[], edge edgeArray[])
{
	FILE *fp;
	if ((fp = fopen("Graph.txt", "r")) == NULL)
	{
		cerr << "The file can not be open" << endl;
		exit(1);
	}
	char a, b;
	int index = 0;
	while (fscanf(fp, "(%c,%c)", &a, &b) == 2)
	{
		int i = 0, j = 0;
		while (verArray[i++] != a);
		while (verArray[j++] != b);
		edgeArray[index].x = --i;
		edgeArray[index].y = --j;
		index++;
	}
	edgeArray[index].x = -1;
	edgeArray[index].y = -1;
	fclose(fp);
	return index;

}

//依据已经建立好的邻接矩阵得到初始顶点数组和边结点数组
void MatrixRegainEdges(graph pGraph, char pVer[], edge pEdge[])
{
	int i = 0;
	int j = 0;
	while (i < pGraph.numVertex)
	{
		pVer[i] = pGraph.vertex[i];
		i++;
	}

	pVer[i] = '$';

	int k = 0;
	for (i = 0; i < pGraph.numVertex; i++)
	{
		for (j = 0; j < pGraph.numVertex; j++)
		{
			if (pGraph.edge[i][j] == 1)
			{
				pEdge[k].x = i;
				pEdge[k].y = j;
				k++;
			}
		}
	}
	pEdge[k].x = -1;
	pEdge[k].y = -1;

}
//边结点数目有待改进为已有边数目；
//邻接矩阵转换邻接表
void AdjMatrixTranToAdjList(graph pGraph, AdjListGraph &alGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	MatrixRegainEdges(pGraph, pVer, pEdge);
	alGraph.CreatAdjListGraph(pVer, pEdge);
}
//邻接矩阵转化十字链表
void AdjMatrixTranToOrthList(graph pGraph, OListGraph &olGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	MatrixRegainEdges(pGraph, pVer, pEdge);
	olGraph.CreatOListGraph(pVer, pEdge);
}

//从邻接表找到初始的顶点数组和边结点数组
void RegainAdjListEdges(adjGraph adjGraph, char pVer[], edge pEdge[])
{
	int i = 0;
	int j = 0;
	while (i < adjGraph.numVertex)
	{
		pVer[i] = adjGraph.vexList[i].vertex;                 //顶点数组
		edgeNode *pNode;
		pNode = adjGraph.vexList[i].firstEdge;
		while (pNode != NULL)
		{
			pEdge[j].x = i;
			pEdge[j].y = pNode->adjvex;                        //边结点
			pNode = pNode->next;
			j++;
		}
		i++;
	}
	pVer[i] = '$';                          //顶点数组最后标志 $
	pEdge[j].x = -1;                       // 边结点数组 最后标志-1，-1
	pEdge[j].y = -1;
}
//邻接表转换邻接矩阵
void AdjListTranToAdjMatrix(adjGraph aGraph, AdjMatrixGraph &amGrap)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	RegainAdjListEdges(aGraph, pVer, pEdge);
	amGrap.CreatAdjacencyMatrix(pVer, pEdge);

}
//邻接表转十字链表
void AdjListTranToOrthList(adjGraph aGraph, OListGraph &olGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	RegainAdjListEdges(aGraph, pVer, pEdge);
	olGraph.CreatOListGraph(pVer, pEdge);
}


//依据十字列表得到初始顶点数组和边结点数组
void OListRegainEdges(olGraph oGraph, char pVer[], edge pEdge[])
{
	int i = 0;                        //i纪录顶点下标
	int k = 0;                      //k 纪录边结点数组下标
	while (i < oGraph.numVertex)
	{

		pVer[i] = oGraph.xlist[i].vextex;               //建立顶点数组
		edgeBox *pNode;
		pNode = oGraph.xlist[i].firstout;
		while (pNode != NULL)                           //建立边结点数组
		{
			pEdge[k].x = i;
			pEdge[k].y = pNode->tailvex;                 //EROOR 更新
			pNode = pNode->hlink;
			k++;
		}
		i++;
	}
	pVer[i] = '$';
	pEdge[k].x = -1;
	pEdge[k].y = -1;

}

//十字表转邻接矩阵
void OListTranToMatrix(olGraph oGraph, AdjMatrixGraph &amGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];

	OListRegainEdges(oGraph, pVer, pEdge);
	amGraph.CreatAdjacencyMatrix(pVer, pEdge);
}
//十字表转邻接表
void OListTranToAdjList(olGraph oGraph, AdjListGraph &alGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	OListRegainEdges(oGraph, pVer, pEdge);
	alGraph.CreatAdjListGraph(pVer, pEdge);
}

int main()
{

	while (1)
	{
		printf("\t________________________________________\n");
		printf("\n");
		printf("\t          *图的实现、搜索及转换*        \n");
		printf("\t________________________________________\n");
		printf("\t________________________________________\n");
		printf("\t|                                       |\n");
		printf("\t| 1.图的存储                            |\n");
		printf("\t| 2.图的搜索                            |\n");
		printf("\t| 3.图的存储结构的转换                  |\n");
		printf("\t| 0.退出                                |\n");
		printf("\t|_______________________________________|\n");
		char c;
		do
		{
			printf("\t请选择（0-3）：");
			c = getch();
			if (c<'0' || c>'3')
			{
				printf("\t输入错误！\n");
			}

		} while (c<'0' || c>'3');

		char A[10] = {};
		edge myEdge[15];
		FindVertices(A, 10);
		FindEdge(A, myEdge);
		AdjMatrixGraph p, ListTranMat, OListTranMat;
		AdjListGraph g, MatTranList, OListTranList;
		OListGraph  o, MatTranOList, ListTranOList;
		p.CreatAdjacencyMatrix(A, myEdge);
		g.CreatAdjListGraph(A, myEdge);
		o.CreatOListGraph(A, myEdge);
		if (c == '1')
		{

			p.DisplayGraph();
			g.DisplayGraph();
			o.DisplayGraph();
		}
		else if (c == '2')
		{
			printf("\n邻接矩阵的深度优先搜索(递归）：\n");
			p.DFSTraverse();
			printf("\n邻接矩阵的深度优先搜索（非递归）:\n");
			p.NonRecDFSTraverse();
			printf("\n邻接矩阵的广度优先搜索：\n");
			p.BFSTraverse();

			printf("\n邻接表深度优先搜索(递归)：\n");
			g.DFSAdjListTraverse();
			printf("\n邻接表深度优先搜索(非递归);\n");
			g.NonRecDFSListTraverse();
			printf("\n邻接表广度优先搜索：\n");
			g.BFSAdjListTraverse();


			printf("十字表深度优先搜索(递归)：\n");
			o.DFSOListTraverse();
			printf("十字表深度优先搜索(非递归)：\n");
			o.NonRecDFSOListTraverse();
			printf("十字表广度优先搜索：\n");
			o.BFSOListTraverse();
		}

		else if (c == '3')
		{
			printf("邻接矩阵转换邻接表：\n");
			AdjMatrixTranToAdjList(p.myGraph, MatTranList);
			MatTranList.DisplayGraph();
			printf("邻接矩阵转换十字表：\n");
			AdjMatrixTranToOrthList(p.myGraph, MatTranOList);
			MatTranOList.DisplayGraph();

			printf("邻接表转换邻接矩阵：\n");
			AdjListTranToAdjMatrix(g.myAdjGraph, ListTranMat);
			ListTranMat.DisplayGraph();
			printf("邻接表转换十字表：\n");
			AdjListTranToOrthList(g.myAdjGraph, ListTranOList);
			ListTranOList.DisplayGraph();

			printf("十字表转换邻接矩阵：\n");
			OListTranToMatrix(o.myOListGraph, OListTranMat);
			OListTranMat.DisplayGraph();
			printf("十字表转换邻接表：\n");
			OListTranToAdjList(o.myOListGraph, OListTranList);
			OListTranList.DisplayGraph();
		}

		else
		{
			printf("\t欢迎再次使用^-^\n");
			exit(0);
		}
		system("pause");
		system("cls");
	}
	return 0;

}