#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "OrthogonalList.h"

using namespace std;

//���ļ���ȡͼ����Ϣ����ȡ�������verArray������
//���������Ϊ��$����־�����ض������Ŀ��
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

//���ļ���ȡͼ����Ϣ����ȡ�ߴ���edgeArray������
//���������Ϊ��0��0�������رߵ���Ŀ
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

//�����Ѿ������õ��ڽӾ���õ���ʼ��������ͱ߽������
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
//�߽����Ŀ�д��Ľ�Ϊ���б���Ŀ��
//�ڽӾ���ת���ڽӱ�
void AdjMatrixTranToAdjList(graph pGraph, AdjListGraph &alGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	MatrixRegainEdges(pGraph, pVer, pEdge);
	alGraph.CreatAdjListGraph(pVer, pEdge);
}
//�ڽӾ���ת��ʮ������
void AdjMatrixTranToOrthList(graph pGraph, OListGraph &olGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	MatrixRegainEdges(pGraph, pVer, pEdge);
	olGraph.CreatOListGraph(pVer, pEdge);
}

//���ڽӱ��ҵ���ʼ�Ķ�������ͱ߽������
void RegainAdjListEdges(adjGraph adjGraph, char pVer[], edge pEdge[])
{
	int i = 0;
	int j = 0;
	while (i < adjGraph.numVertex)
	{
		pVer[i] = adjGraph.vexList[i].vertex;                 //��������
		edgeNode *pNode;
		pNode = adjGraph.vexList[i].firstEdge;
		while (pNode != NULL)
		{
			pEdge[j].x = i;
			pEdge[j].y = pNode->adjvex;                        //�߽��
			pNode = pNode->next;
			j++;
		}
		i++;
	}
	pVer[i] = '$';                          //������������־ $
	pEdge[j].x = -1;                       // �߽������ ����־-1��-1
	pEdge[j].y = -1;
}
//�ڽӱ�ת���ڽӾ���
void AdjListTranToAdjMatrix(adjGraph aGraph, AdjMatrixGraph &amGrap)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	RegainAdjListEdges(aGraph, pVer, pEdge);
	amGrap.CreatAdjacencyMatrix(pVer, pEdge);

}
//�ڽӱ�תʮ������
void AdjListTranToOrthList(adjGraph aGraph, OListGraph &olGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];
	RegainAdjListEdges(aGraph, pVer, pEdge);
	olGraph.CreatOListGraph(pVer, pEdge);
}


//����ʮ���б�õ���ʼ��������ͱ߽������
void OListRegainEdges(olGraph oGraph, char pVer[], edge pEdge[])
{
	int i = 0;                        //i��¼�����±�
	int k = 0;                      //k ��¼�߽�������±�
	while (i < oGraph.numVertex)
	{

		pVer[i] = oGraph.xlist[i].vextex;               //������������
		edgeBox *pNode;
		pNode = oGraph.xlist[i].firstout;
		while (pNode != NULL)                           //�����߽������
		{
			pEdge[k].x = i;
			pEdge[k].y = pNode->tailvex;                 //EROOR ����
			pNode = pNode->hlink;
			k++;
		}
		i++;
	}
	pVer[i] = '$';
	pEdge[k].x = -1;
	pEdge[k].y = -1;

}

//ʮ�ֱ�ת�ڽӾ���
void OListTranToMatrix(olGraph oGraph, AdjMatrixGraph &amGraph)
{
	char pVer[numVertices];
	edge pEdge[numVertices * 2];

	OListRegainEdges(oGraph, pVer, pEdge);
	amGraph.CreatAdjacencyMatrix(pVer, pEdge);
}
//ʮ�ֱ�ת�ڽӱ�
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
		printf("\t          *ͼ��ʵ�֡�������ת��*        \n");
		printf("\t________________________________________\n");
		printf("\t________________________________________\n");
		printf("\t|                                       |\n");
		printf("\t| 1.ͼ�Ĵ洢                            |\n");
		printf("\t| 2.ͼ������                            |\n");
		printf("\t| 3.ͼ�Ĵ洢�ṹ��ת��                  |\n");
		printf("\t| 0.�˳�                                |\n");
		printf("\t|_______________________________________|\n");
		char c;
		do
		{
			printf("\t��ѡ��0-3����");
			c = getch();
			if (c<'0' || c>'3')
			{
				printf("\t�������\n");
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
			printf("\n�ڽӾ���������������(�ݹ飩��\n");
			p.DFSTraverse();
			printf("\n�ڽӾ������������������ǵݹ飩:\n");
			p.NonRecDFSTraverse();
			printf("\n�ڽӾ���Ĺ������������\n");
			p.BFSTraverse();

			printf("\n�ڽӱ������������(�ݹ�)��\n");
			g.DFSAdjListTraverse();
			printf("\n�ڽӱ������������(�ǵݹ�);\n");
			g.NonRecDFSListTraverse();
			printf("\n�ڽӱ�������������\n");
			g.BFSAdjListTraverse();


			printf("ʮ�ֱ������������(�ݹ�)��\n");
			o.DFSOListTraverse();
			printf("ʮ�ֱ������������(�ǵݹ�)��\n");
			o.NonRecDFSOListTraverse();
			printf("ʮ�ֱ�������������\n");
			o.BFSOListTraverse();
		}

		else if (c == '3')
		{
			printf("�ڽӾ���ת���ڽӱ�\n");
			AdjMatrixTranToAdjList(p.myGraph, MatTranList);
			MatTranList.DisplayGraph();
			printf("�ڽӾ���ת��ʮ�ֱ�\n");
			AdjMatrixTranToOrthList(p.myGraph, MatTranOList);
			MatTranOList.DisplayGraph();

			printf("�ڽӱ�ת���ڽӾ���\n");
			AdjListTranToAdjMatrix(g.myAdjGraph, ListTranMat);
			ListTranMat.DisplayGraph();
			printf("�ڽӱ�ת��ʮ�ֱ�\n");
			AdjListTranToOrthList(g.myAdjGraph, ListTranOList);
			ListTranOList.DisplayGraph();

			printf("ʮ�ֱ�ת���ڽӾ���\n");
			OListTranToMatrix(o.myOListGraph, OListTranMat);
			OListTranMat.DisplayGraph();
			printf("ʮ�ֱ�ת���ڽӱ�\n");
			OListTranToAdjList(o.myOListGraph, OListTranList);
			OListTranList.DisplayGraph();
		}

		else
		{
			printf("\t��ӭ�ٴ�ʹ��^-^\n");
			exit(0);
		}
		system("pause");
		system("cls");
	}
	return 0;

}