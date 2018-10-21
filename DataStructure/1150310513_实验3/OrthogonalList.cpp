#include <iostream>
#include "OrthogonalList.h"
using namespace std;

//����ͼ��ʮ�ֱ�洢��ʽ�Ľ���
void OListGraph::CreatOListGraph(char pVer[], edge pEdge[])
{
	int i = 0;
	while (pVer[i] != '$')                             //����ͷ�ṹ
	{
		myOListGraph.xlist[i].vextex = pVer[i];
		myOListGraph.xlist[i].firstout = NULL;
		myOListGraph.xlist[i].firstin = NULL;
		i++;
	}
	myOListGraph.numVertex = i;

	i = 0;
	int m, n;
	while (pEdge[i].x != -1 && pEdge[i].y != -1)
	{
		m = pEdge[i].x;
		n = pEdge[i].y;
		edgeBox *pNode = new edgeBox;

		pNode->headvex = m;
		pNode->tailvex = n;
		pNode->hlink = myOListGraph.xlist[m].firstout;
		myOListGraph.xlist[m].firstout = pNode;
		pNode->tlink = myOListGraph.xlist[n].firstin;
		myOListGraph.xlist[n].firstin = pNode;
		i++;
	}
}

void OListGraph::DisplayGraph()
{
	printf("ʮ������\n");
	int i = 0;
	printf("OutEdge:\n");
	while (i < myOListGraph.numVertex)
	{
		printf("����%c�� ", myOListGraph.xlist[i].vextex);
		edgeBox *pNode;
		pNode = myOListGraph.xlist[i].firstout;
		while (pNode != NULL)
		{
			printf("%c ", myOListGraph.xlist[pNode->tailvex].vextex);
			pNode = pNode->hlink;
		}
		printf("\n");
		i++;

	}

	printf("InEdge:\n");
	i = 0;
	while (i < myOListGraph.numVertex)
	{
		printf("����%c�� ", myOListGraph.xlist[i].vextex);
		edgeBox *pNode;
		pNode = myOListGraph.xlist[i].firstin;
		while (pNode != NULL)
		{
			printf("%c ", myOListGraph.xlist[pNode->headvex].vextex);
			pNode = pNode->tlink;
		}
		printf("\n");
		i++;
	}
}

void OListGraph::DestroyGraph()
{

	int i = 0;
	edgeBox* pNode;
	while (i<myOListGraph.numVertex)
	{
		if (myOListGraph.xlist[i].firstout == NULL)
		{
			i++; continue;
		}
		while (myOListGraph.xlist[i].firstout->hlink != NULL)
		{
			pNode = myOListGraph.xlist[i].firstout->hlink;
			delete myOListGraph.xlist[i].firstout;
			myOListGraph.xlist[i].firstout = pNode;
		}
		delete myOListGraph.xlist[i].firstout;
		i++;

	}
}


int countOList;
void OListGraph::visit(int i)
{
	printf("%c ", myOListGraph.xlist[i].vextex);
}

void OListGraph::DFSOListTraverse()
{
	int i;
	countOList = 0;
	for (i = 0; i < myOListGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myOListGraph.numVertex; i++)
	{
		if (!visited[i])
			DFSOList(i);
	}
	printf("\n");
}
void OListGraph::DFSOList(int i)
{
	edgeBox *pNode;
	visit(i);
	visited[i] = true;
	dfn[i] = countOList++;
	pNode = myOListGraph.xlist[i].firstout;
	while (pNode != NULL)
	{
		if (!visited[pNode->tailvex])
			DFSOList(pNode->tailvex);
		pNode = pNode->hlink;
	}
}

void OListGraph::NonRecDFSOListTraverse()
{
	int i;
	for (i = 0; i < myOListGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i <myOListGraph.numVertex; i++)
	{
		if (!visited[i])
			NonRecDFSOList(i);
	}
	printf("\n");
}

void OListGraph::NonRecDFSOList(int i)
{
	stack<int> S;
	edgeBox *pNode;
	visit(i);
	visited[i] = true;
	S.push(i);

	while (!S.empty())
	{
		i = S.top();
		pNode = myOListGraph.xlist[i].firstout;
		while (pNode != NULL)                     //����ǰ����û���ڽӶ��㣬��ջ
		{
			if (!visited[pNode->tailvex])
			{
				visit(pNode->tailvex);
				visited[pNode->tailvex] = true;
				S.push(pNode->tailvex);
				break;
			}
			pNode = pNode->hlink;
		}
		if (pNode == NULL)                  //ֻ�е�ĳһ����������ڽӷ�����֮��pop
			S.pop();
	}
}

void OListGraph::BFSOListTraverse()
{
	int i;
	countOList = 0;
	for (i = 0; i < myOListGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myOListGraph.numVertex; i++)
	{
		if (!visited[i])
			BFSOList(i);
	}
	printf("\n");
}

void OListGraph::BFSOList(int i)
{
	int j;
	queue<int> Q;
	edgeBox *pNode;
	visit(i);
	visited[i] = true;
	bfn[i] = countOList++;
	while (!Q.empty())
	{
		j = Q.front();
		Q.pop();
		pNode = myOListGraph.xlist[i].firstout;
		while (pNode != NULL)
		{
			if (!visited[pNode->tailvex])
			{
				visit(pNode->tailvex);
				visited[pNode->tailvex] = true;
				bfn[pNode->tailvex] = countOList++;
				Q.push(pNode->tailvex);
			}
			pNode = pNode->hlink;
		}
	}
}