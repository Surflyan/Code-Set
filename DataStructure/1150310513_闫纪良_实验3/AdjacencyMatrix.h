#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX
#include "define.h"


typedef struct                                //有向图的邻接矩阵存储结构
{
	char vertex[numVertices];                 //顶点
	int  edge[numVertices][numVertices];      //边
	int numVertex;
	int numEdge;
}graph;


class AdjMatrixGraph
{
public:
	AdjMatrixGraph() { InitGraph(); }
	void CreatAdjacencyMatrix(char pVer[], edge pEdge[]);      //建立有向图的邻接矩阵存储结构
	void InitGraph();                                          //初始化图

	void DisplayGraph();                                       //有向图的输出

	void DFSTraverse();                                       //有向图邻接矩阵存储形式的深度优先搜索（递归）
	void DFSAdjMatrix(int i);
	void visit(int i);

	void NonRecDFSTraverse();                                 //有向图的邻接矩阵存储形式的深度优先搜索（非递归）
	void NonRecDFSAdjMatrix(int i);

	void BFSTraverse();                                        //有向图的邻接矩阵存储形式的广度优先搜索
	void BFSAdjMatrix(int i);

	graph myGraph;
	bool visited[numVertices];                               //搜索标志
	int dfn[numVertices];                                    //深搜序列
	int bfn[numVertices];                                    //广搜序列
};



#endif 
