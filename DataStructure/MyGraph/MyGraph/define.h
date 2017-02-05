/*本程序图的最大顶点数在全局变量numVertices设定，
该程序设为15，边的数目设为2*numVertices；（注，应另设全局变量，方便修改
本程序只有递归深度优先记录了DFN编号和BFN编号；

*/

#ifndef DEFINE_H
#define DEFINE_H
#include <stack>
#include <queue>
#define numVertices 15             //最大顶点数


typedef struct                      //边结点，存储边的两个邻接点
{
	int  x;
	int  y;
}edge;


#endif 
