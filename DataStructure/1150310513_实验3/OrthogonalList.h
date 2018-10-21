#ifndef ORTHOGONAL_LIST_H
#define ORTHOGONAL_LIST_H
#include "define.h"

struct edgeBox                      //边结点结构
{
	int  headvex, tailvex;          //该边的尾和首顶点的位置
	edgeBox *hlink, *tlink;        //边首相同和边尾相同的边的链域

};

struct vexNode                     //头结点结构
{
	char vextex;
	edgeBox *firstin, *firstout;    //分别指向该顶点第一条入边和出边

};

struct olGraph
{
	vexNode  xlist[numVertices];         //表头向量
	int numVertex;                       //有向图的当前顶点数和边数
	int numEdge;
};

class OListGraph
{
public:
	OListGraph() {};
	void CreatOListGraph(char pVer[], edge pEdge[]);                //建立十字表的存储结构
	void DestroyGraph();                                            //销毁
	void DisplayGraph();                                             //输出

	void DFSOListTraverse();                                        //深度优先搜索（递归）
	void DFSOList(int i);
	void visit(int i);
	void NonRecDFSOListTraverse();                                  //深度优先搜索（非递归）
	void NonRecDFSOList(int i);

	void BFSOListTraverse();                                          //广度优先搜索
	void BFSOList(int i);
	~OListGraph() { DestroyGraph(); };

	olGraph myOListGraph;
	bool visited[numVertices];
	int dfn[numVertices];
	int bfn[numVertices];
};

#endif 
