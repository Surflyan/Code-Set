#include <iostream>

#define pi 3.14159265358

using namespace std;


  //二维点类
class Point                          
{
public:

	Point(double x = 0, double y = 0);
	~Point() {};

	void set_point(double x, double y);

	double get_x() const;
	double get_y() const;

	void display_point() const;

protected:
	double m_x;
	double m_y;
};

Point::Point(double x, double y) :m_x(x), m_y(y)
{}

void Point::set_point(double x, double y)
{
	m_x = x;
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

void Point::display_point() const
{
	cout << '(' << m_x << ',' << m_y << ')' << endl;
}


 
//圆类
class Circle : public Point             
{
public:
	Circle(double x = 0, double y = 0, double r = 0);
	~Circle() {};

	void set_rad(double r);
	double get_rad() const;

	double area_f() ;
	double area;

private:
	double  rad;
	
};

Circle::Circle(double x, double y, double r) :
	Point(x, y), rad(r)
{}

void Circle::set_rad(double r)  //mark
{
	rad = r;
}

double Circle::get_rad() const
{
	return rad;
}

double Circle::area_f() 
{
	area = pi* rad * rad;
	return area;
}



//圆柱体类
class Cylinder : public Circle
{
public :
	Cylinder(double x=0, double y=0 , double r=0 , double h=0 );
	~Cylinder() {};

	void set_high(double h);
	double get_high() const;

	double volume_f();

private:
	double high;
	double volume;
};


Cylinder::Cylinder(double x,double y,double r,double h):
	Circle(x,y,r), high(h)
{}

void Cylinder::set_high(double h)
{
	high = h;
}

double Cylinder::get_high() const
{
	return high;
}

double Cylinder::volume_f()
{
	volume = area * high;
	return volume;
}
int main()
{
	Cylinder c1(0.0, 0.0, 2,2);

	cout << "coordinate:";
	c1.display_point();
	cout <<"area="<< c1.area_f() << endl;
	cout << "volume=" << c1.volume_f() << endl;

}