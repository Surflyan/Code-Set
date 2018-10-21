#include <iostream>

#include "AdjacencyList.h"
using namespace std;

//����ͼ���ڽӱ�Ľ���
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
	while (pEdge[i].x != -1 && pEdge[i].y != -1)                   //�߽ṹ�Ľ���
	{
		edgeNode *pNode = new edgeNode;
		pNode->adjvex = pEdge[i].y;                                 //�ߵ���ͬͷ���㣬��ͬβ����
		pNode->next = myAdjGraph.vexList[pEdge[i].x].firstEdge;
		myAdjGraph.vexList[pEdge[i].x].firstEdge = pNode;
		i++;
	}
	myAdjGraph.numEdge = i;

}

//�ͷ��ڽӱ�
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

//����ڽӱ��ʾ��ͼ��������㣨���±�)
void AdjListGraph::DisplayGraph()
{
	int i = 0;
	printf("\n�ڽӱ� ��\n");
	while (i < myAdjGraph.numVertex)
	{
		printf("���� %c: ", myAdjGraph.vexList[i].vertex);
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

int countList;           //ȫ�ֱ�������DFS���б��

						 //������ȱ������㷨
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
//��һ�����������������ȱ����㷨��
//��ViΪ��������ڽӱ��ʾ��ͼ������������
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

////�ǵݹ���������ڽӱ���������ɭ�ֵ�������
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

//�ǵݹ������������
void AdjListGraph::NonRecDFSList(int i)
{
	stack<int> S;
	edgeNode *pNode;
	visit(i);
	visited[i] = true;                                   //���ʵ�ǰ���㣬��ѹջ
	S.push(i);

	while (!S.empty())
	{
		i = S.top();
		pNode = myAdjGraph.vexList[i].firstEdge;
		while (pNode != NULL)                     //��ջ������û���ڽӶ��㣬��ջ
		{
			if (!visited[pNode->adjvex])                //����ջ������δ�����ڽӶ��㣬��ѹջ
			{
				visit(pNode->adjvex);
				visited[pNode->adjvex] = true;
				S.push(pNode->adjvex);
				break;
			}
			pNode = pNode->next;
		}
		if (pNode == NULL)                  //ֻ�е�ĳһ����������ڽӷ�����֮��pop
			S.pop();
	}
}

//�����������������
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

//�����������
void AdjListGraph::BFSAdjList(int i)
{
	int j;
	queue<int> Q;                       //���ʵ�ǰ���㲢���
	edgeNode *pNode;
	visit(i);
	visited[i] = true;
	bfn[i] = countList++;
	while (!Q.empty())
	{
		j = Q.front();
		Q.pop();
		pNode = myAdjGraph.vexList[i].firstEdge;           //���ʶ��׶���������ڽӶ��㣬���������
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