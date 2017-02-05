//实现三维点类的方法
#include <iostream>
#include "Point3D.h"

using namespace std;


Point::Point(double x, double y) :m_x(x), m_y(y)
{}

void Point::set_x(double x)
{
	m_x = x;
}

void Point::set_y(double y)
{
	m_y = y;
}

double Point::get_x() const
{
	return  m_x;
}

double  Point::get_y() const
{
	return m_y;
}



Point3D::Point3D(double x, double y, double z) :
	Point(x, y), m_z(z)
{
}


void Point3D::set_z(double z)
{
	m_z = z;
}

double Point3D::get_z()
{
	return m_z;
}

void Point3D::display_point() const
{
	cout << m_x << ',' << m_y << ',' << m_z << endl;
}
