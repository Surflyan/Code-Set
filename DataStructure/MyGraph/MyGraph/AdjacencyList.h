
#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST
#include "define.h"

struct edgeNode
{                              //�߱�
	int  adjvex;
	edgeNode *next;

};

typedef struct
{
	char vertex;                     //�����
	edgeNode *firstEdge;
}vertexNode;

typedef struct
{                                   //����ͼ���ڽӱ�洢�ṹ
	vertexNode vexList[numVertices];
	int numVertex;
	int numEdge;
}adjGraph;

class AdjListGraph
{
public:
	AdjListGraph() {}
	void CreatAdjListGraph(char pVer[], edge pEdge[]);      //����ͼ�ڽӱ�洢�ṹ�Ľ���
	void DestroyAdjList();                                  //����
	void DisplayGraph();                                     //���
	void DFSAdjListTraverse();                               //�ڽӱ���������������������ݹ飩
	void DFSAdjList(int i);                                  //�ڽӱ������������
	void NonRecDFSListTraverse();                            //�ڽӱ���������������ǵݹ飩
	void NonRecDFSList(int i);
	void visit(int i);                                       //���ʺ���

	void BFSAdjListTraverse();                                //�ڽӱ�Ĺ����������
	void BFSAdjList(int i);

	~AdjListGraph() { DestroyAdjList(); }

	adjGraph myAdjGraph;
	bool visited[numVertices];
	int dfn[numVertices];
	int bfn[numVertices];
};


#endif
