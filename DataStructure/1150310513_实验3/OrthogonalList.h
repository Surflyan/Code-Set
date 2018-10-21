#ifndef ORTHOGONAL_LIST_H
#define ORTHOGONAL_LIST_H
#include "define.h"

struct edgeBox                      //�߽��ṹ
{
	int  headvex, tailvex;          //�ñߵ�β���׶����λ��
	edgeBox *hlink, *tlink;        //������ͬ�ͱ�β��ͬ�ıߵ�����

};

struct vexNode                     //ͷ���ṹ
{
	char vextex;
	edgeBox *firstin, *firstout;    //�ֱ�ָ��ö����һ����ߺͳ���

};

struct olGraph
{
	vexNode  xlist[numVertices];         //��ͷ����
	int numVertex;                       //����ͼ�ĵ�ǰ�������ͱ���
	int numEdge;
};

class OListGraph
{
public:
	OListGraph() {};
	void CreatOListGraph(char pVer[], edge pEdge[]);                //����ʮ�ֱ�Ĵ洢�ṹ
	void DestroyGraph();                                            //����
	void DisplayGraph();                                             //���

	void DFSOListTraverse();                                        //��������������ݹ飩
	void DFSOList(int i);
	void visit(int i);
	void NonRecDFSOListTraverse();                                  //��������������ǵݹ飩
	void NonRecDFSOList(int i);

	void BFSOListTraverse();                                          //�����������
	void BFSOList(int i);
	~OListGraph() { DestroyGraph(); };

	olGraph myOListGraph;
	bool visited[numVertices];
	int dfn[numVertices];
	int bfn[numVertices];
};

#endif 
