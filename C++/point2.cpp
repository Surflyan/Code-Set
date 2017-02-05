#include <iostream>

using namespace std;

class Point                            //二维点类
{
public:
	
	Point(double x=0, double y=0);
	~Point() {};

	double get_x() const;
	double get_y() const;

	void set_x(double x);
	void set_y(double y);

	void display_point() const;

protected:
	double m_x;
	double m_y;
};

Point::Point(double x,double y)
{
	m_x = x;
	m_y = y;
}

double Point::get_x() const
{
	return m_x;
}

double Point::get_y() const
{
	return m_y;
}

void Point::set_x(double x)
{
	m_x = x;
}
void Point::set_y(double y)
{
	m_y = y;
}

void Point::display_point() const
{
	cout << "(" << m_x << "," << m_y << ")" << endl;
}

class Point3D : public Point            //三维点 派生类
{
public:
	Point3D(double x=0, double y=0, double z=0);

	void set_z(double z);
	double get_z() const;

	void display_point() const;

private :
	double m_z;

};

Point3D::Point3D(double x, double y, double z) : Point(x, y), m_z(z)
{}

double Point3D::get_z() const
{
	return m_z;
}

void Point3D::set_z(double z)
{
	m_z = z;
}

void Point3D::display_point() const
{
	cout << '(' << m_x << ',' << m_y << ',' << m_z << ')' << endl;
}

int main()
{   
	double x, y, z;
	cout << "请输入点的三维坐标：" << endl;
	cout << "x=";  cin >> x;
	cout << "y="; cin >> y;
	cout << "z="; cin >> z;

	Point3D p1(x, y, z);           
	p1.display_point();                  //输出点坐标


}