#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "define.h"


typedef struct                                //����ͼ���ڽӾ���洢�ṹ
{
	char vertex[numVertices];                 //����
	int  edge[numVertices][numVertices];      //��
	int numVertex;
	int numEdge;
}graph;


class AdjMatrixGraph
{
public:
	AdjMatrixGraph() { InitGraph(); }
	void CreatAdjacencyMatrix(char pVer[], edge pEdge[]);      //��������ͼ���ڽӾ���洢�ṹ
	void InitGraph();                                          //��ʼ��ͼ

	void DisplayGraph();                                       //����ͼ�����

	void DFSTraverse();                                       //����ͼ�ڽӾ���洢��ʽ����������������ݹ飩
	void DFSAdjMatrix(int i);
	void visit(int i);

	void NonRecDFSTraverse();                                 //����ͼ���ڽӾ���洢��ʽ����������������ǵݹ飩
	void NonRecDFSAdjMatrix(int i);

	void BFSTraverse();                                        //����ͼ���ڽӾ���洢��ʽ�Ĺ����������
	void BFSAdjMatrix(int i);

	graph myGraph;
	bool visited[numVertices];                               //������־
	int dfn[numVertices];                                    //��������
	int bfn[numVertices];                                    //��������
};



#endif 
