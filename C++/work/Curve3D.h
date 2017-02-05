#include <iostream>
#include "Point3D.h"

#ifndef M_CURVE3D_H
#define M_CURVE3D_H


//折线类
class Curve3D
{

public:
	Curve3D(double x = 0, double y = 0, double z = 0);
	Curve3D(const Curve3D &ptrline);

	~Curve3D();

	void display_curve() const;        //输出折线所含点坐标
	double curve_len() const;          // 计算折线长度


	Curve3D & operator=(Curve3D & pline);        
	Curve3D  operator+(Point3D &point);
	Curve3D  operator-(Point3D &point);

	int  write_txt(ofstream &os);         //读写文件
	int  read_txt(ifstream &in);
	int  write_binary(ofstream &os);
	int read_binary(ifstream &is);

private:
	int point_num = 0;           //纪录当前折线所含点数目
	Point3D *p;                //指向折线包含的点的地址
	int max_number;          // 当前申请空间点最大容量


};
#endif;