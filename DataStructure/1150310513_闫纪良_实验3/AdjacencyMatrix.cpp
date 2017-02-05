#include <iostream>
#include "AdjacencyMatrix.h"
using namespace std;

//ͼ�ĳ�ʼ��
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
//����ͼ�ڽӾ�����ʽ�ĵĽ���
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

//����ͼ�ڽӾ������ʾ
void AdjMatrixGraph::DisplayGraph()
{
	int i;
	int j;
	printf("\n�ڽӾ��� \n");
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

int countMatrix;                 //ȫ�ֱ������������б��ʹ��

								 //��ȵݹ�������������ɭ�ֵ�������
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

//��ȵݹ�����ĳ����
void AdjMatrixGraph::DFSAdjMatrix(int i)
{
	int j;
	visit(i);                       //���ʸö���
	visited[i] = true;
	dfn[i] = countMatrix++;

	for (j = 0; j < myGraph.numVertex; j++)
	{
		if ((myGraph.edge[i][j] == 1) && !visited[j])
			DFSAdjMatrix(j);
	}
}

//���ʺ���
void AdjMatrixGraph::visit(int i)
{
	printf("%c ", myGraph.vertex[i]);
}


//�ǵݹ��������ͼ���ڽӾ���洢��ʽ
//û��������������
void AdjMatrixGraph::NonRecDFSTraverse()
{
	int i;
	for (i = 0; i < myGraph.numVertex; i++)
		visited[i] = false;
	for (i = 0; i < myGraph.numVertex; i++)               //������������ͨ����
	{
		if (!visited[i])
			NonRecDFSAdjMatrix(i);
	}

}

//�ǵݹ�����
void AdjMatrixGraph::NonRecDFSAdjMatrix(int index)
{
	stack<int>S;
	int j;
	visit(index);
	visited[index] = true;                       //���ʸýڵ㣬����֮ѹջ
	S.push(index);

	while (!S.empty())
	{
		index = S.top();                         //������ýڵ��ڽӵĶ���
		for (j = 0; j < myGraph.numVertex; j++)
		{
			if (myGraph.edge[index][j] == 1 && !visited[j])     //����δ�����ڽӵ㶥�㣬����ʺ�ѹջ
			{
				visit(j);
				visited[j] = true;
				S.push(j);
				break;
			}
		}
		if (j == myGraph.numVertex)                                //����δ�����ڽӶ��㣬��ջ�������ϸ�������¸��ڽӶ���
		{
			S.pop();
		}
	}
}

//�����������������
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

//����������������У�
void AdjMatrixGraph::BFSAdjMatrix(int i)
{
	queue<int> Q;
	int j, k;
	visit(i);                                        //���ʵ�ǰ��㣬�����
	visited[i] = true;
	bfn[i] = countMatrix++;
	Q.push(i);
	while (!Q.empty())
	{
		j = Q.front();                                    //�����뵱ǰ����ڽӵ��������㲢�������
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