#include <iostream>
#include "Point3D.h"

#ifndef M_CURVE3D_H
#define M_CURVE3D_H


//������
class Curve3D
{

public:
	Curve3D(double x = 0, double y = 0, double z = 0);
	Curve3D(const Curve3D &ptrline);

	~Curve3D();

	void display_curve() const;        //�����������������
	double curve_len() const;          // �������߳���


	Curve3D & operator=(Curve3D & pline);        
	Curve3D  operator+(Point3D &point);
	Curve3D  operator-(Point3D &point);

	int  write_txt(ofstream &os);         //��д�ļ�
	int  read_txt(ifstream &in);
	int  write_binary(ofstream &os);
	int read_binary(ifstream &is);

private:
	int point_num = 0;           //��¼��ǰ������������Ŀ
	Point3D *p;                //ָ�����߰����ĵ�ĵ�ַ
	int max_number;          // ��ǰ����ռ���������


};
#endif;