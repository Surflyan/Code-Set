
#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST
#include "define.h"

struct edgeNode
{                              //边表
	int  adjvex;
	edgeNode *next;

};

typedef struct
{
	char vertex;                     //顶点表
	edgeNode *firstEdge;
}vertexNode;

typedef struct
{                                   //有向图的邻接表存储结构
	vertexNode vexList[numVertices];
	int numVertex;
	int numEdge;
}adjGraph;

class AdjListGraph
{
public:
	AdjListGraph() {}
	void CreatAdjListGraph(char pVer[], edge pEdge[]);      //有向图邻接表存储结构的建立
	void DestroyAdjList();                                  //销毁
	void DisplayGraph();                                     //输出
	void DFSAdjListTraverse();                               //邻接表深度优先搜索主函数（递归）
	void DFSAdjList(int i);                                  //邻接表深度优先搜索
	void NonRecDFSListTraverse();                            //邻接表深度优先搜索（非递归）
	void NonRecDFSList(int i);
	void visit(int i);                                       //访问函数

	void BFSAdjListTraverse();                                //邻接表的广度优先搜索
	void BFSAdjList(int i);

	~AdjListGraph() { DestroyAdjList(); }

	adjGraph myAdjGraph;
	bool visited[numVertices];
	int dfn[numVertices];
	int bfn[numVertices];
};


#endif
