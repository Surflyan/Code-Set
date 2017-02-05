#include <iostream>


#ifndef M_POINT3D_H
#define M_POINT3D_H

using namespace std;

//��ά����
class Point
{
public:

	Point(double x = 0, double y = 0);
	~Point() {};

	void set_x(double x);
	void set_y(double y);

	double get_x() const;
	double get_y() const;

protected:
	double m_x;
	double m_y;
};


//��ά������
class Point3D : public Point
{

public:
	Point3D(double x = 0, double y = 0, double z = 0);
	~Point3D() {};

	void set_z(double z);
	double get_z();
	void display_point() const;    //�������

protected:
	double  m_z;


};


#endif;