//实现折线类的方法
#include <iostream>
#include <math.h>
#include <fstream>
#include "Curve3D.h"

using namespace std;

Curve3D::Curve3D(double x, double y, double z)
{
	max_number = 5;
	p = new Point3D[max_number];            //开始申请能容5个点的内存

	p[point_num].set_x(x);             // 初始化 0，0，0
	p[point_num].set_y(y);
	p[point_num].set_z(z);

	point_num++;


}


Curve3D::Curve3D(const Curve3D &ptrline)             //拷贝构造函数，方便返回新生成折线
{
	max_number = ptrline.max_number;
	point_num = ptrline.point_num;

	p = new Point3D[max_number];

	int i = 0;
	while (i < max_number)
	{
		p[i] = ptrline.p[i];
		i++;
	}

}

Curve3D::~Curve3D()
{
	if (p != NULL)                  //释放申请的内存
	{
		delete[] p;
		p = NULL;
	}

}

void Curve3D::display_curve()  const        //依次输出点的信息
{

	int i = 0;

	while (i < point_num)
	{
		cout << "number." << i + 1 << ':';
		this->p[i].display_point();
		i++;
	}

}

double Curve3D::curve_len() const
{                                                 //计算折线长度
	int i = 0;                         
	double dx, dy, dz;
	double dl, length = 0;

	if (point_num == 0 || point_num == 1)
	{
		length = 0;
	}

	while (i < point_num - 1)                  //依次遍历求长度
	{
		dx = p[i].get_x() - p[i + 1].get_x();
		dy = p[i].get_y() - p[i + 1].get_y();
		dz = p[i].get_z() - p[i + 1].get_z();

		dl = sqrt(dx*dx + dy*dy + dz*dz);
		length += dl;
		i++;
	}
	cout << "curve length=" << length << endl;

	return length;

}


Curve3D& Curve3D::operator=(Curve3D & pline)          //重载赋值运算符
{


	if (pline.max_number > this->max_number)         //判断右值折线容纳量，若超过当前默认容纳量，
	{												 //则将当前点的指针指向新申请的更大的内存，将原来申请内存释放；
		delete[]this->p;
		this->p = new Point3D[pline.max_number];
	}

	this->point_num = pline.point_num;
	this->max_number = pline.max_number;

	int i = 0;
	while (i < pline.point_num)
	{
		this->p[i] = pline.p[i];                     //依次赋值
		i++;
	}

	return *this;                               //返回当前对象

}



Curve3D Curve3D::operator+(Point3D &point)           //重载+运算符，向折线中添加点
{
	Curve3D temp;                                    //定义新生成折线
	temp.point_num = this->point_num;
	if (this->max_number == this->point_num)
	{                                                //若当前折线点已存满；则新生成折线最大容纳量因增加；
		delete[] temp.p;
		temp.p = NULL;
		temp.max_number = this->max_number * 2;
		temp.p = new Point3D[temp.max_number];
	}
	if (temp.max_number < this->max_number)
	{
		delete[]temp.p;                                  //若新生成折线最大容纳量小于当前折线容纳量，则增大新折线容纳量
		temp.p = NULL;
		temp.p = new Point3D[this->max_number];
		temp.max_number = this->max_number;
	}

	int i = 0;
	while (i<point_num)
	{
		temp.p[i] = this->p[i];
		i++;                                             //依次将当前折线点和要添加点加到新折线中
	}
	temp.p[point_num] = point;

	temp.point_num++;                      //折线点数++

	return temp;
}


Curve3D Curve3D::operator-(Point3D & point)
{

	int i = 0;
	int flag = -1;          //存要删除的点在折线中的下标
	while (i < point_num)
	{
		if (p[i].get_x() == point.get_x()
			&& p[i].get_y() == point.get_y()            //查找待删除点
			&& p[i].get_z() == point.get_z())
		{
			flag = i;
			break;
		}
		i++;

	}
	if (flag != -1)                 //若此点存在于折线中，则定义删除后的新折线
	{
		Curve3D temp;
		temp.max_number = max_number;
		temp.point_num = point_num - 1;

		if (this->point_num > temp.max_number)
		{                                             //若默认最大点容量不够存当前折线点，则新申请内存
             delete[]temp.p;
		      temp.p = NULL;
		     temp.p = new Point3D[temp.max_number];
		}
		
		i = 0;
		while (i <flag)                                  //跳过要删除点，其余个点赋入新折线
		{
			temp.p[i] = this->p[i];
			i++;

		}

		while (i < this->point_num - 1)
		{
			temp.p[i] = this->p[i + 1];
			i++;
		}

		return temp;

	}
	else                                      //若无此点，返回当前
		return *this;

}


int  Curve3D::write_txt(ofstream &os)             //写入文本文件
{

	int i = 0;
	while (i < this->point_num)
	{
		os << p[i].get_x() << ','
			<< p[i].get_y() << ',' << p[i].get_z() << endl;
		i++;

	}

	return 0;
}

int Curve3D::read_txt(ifstream &in)
{                                         //读取文本文件


	int i = 0;
	double x, y, z;
	char c;
	this->point_num = 0;


	while (!in.eof())
	{
		in >> x >> c >> y >> c >> z;          //取出
		p[i].set_x(x);
		p[i].set_y(y);
		p[i].set_z(z);                     //写到折线中
		point_num++;

		if (point_num == max_number)        //当存的点数目超过类的初始最大容纳量
		{                                    // 申请二倍内存存点
			Point3D *temp = p;

			this->max_number *= 2;
			this->p = new Point3D[max_number];

			int j = 0;
			while (j < point_num)
			{
				p[j] = temp[j];               //将以写入折线的点的信息写到新的点内存
				j++;
			}

			delete[] temp;                //释放原来申请内存
		}
		i++;

	}
	point_num--;                    //去点读取文件时最后一个字符的影响

	return 0;

}

int Curve3D::write_binary(ofstream &os)   //写入二进制文件
{
	int i = 0;
	double x, y, z;
	while (i < this->point_num && i >= 0)
	{
		x = p[i].get_x();                    //取点
		y = p[i].get_y();
		z = p[i].get_z();
		os.write((char*)& x, sizeof(double));   //写入
		os.write((char*)& y, sizeof(double));
		os.write((char*)& z, sizeof(double));
		i++;

	}
	return 0;


}

int Curve3D::read_binary(ifstream &is)           //读取二进制文件
{
	double x, y, z;
	int i = 0;
	this->point_num = 0;
	while (!is.eof())
	{
		is.read((char*)&x, sizeof(double));
		is.read((char*)&y, sizeof(double));
		is.read((char*)&z, sizeof(double));        //读点

		p[i].set_x(x);
		p[i].set_y(y);                        //写到当前折线中
		p[i].set_z(z);


		this->point_num++;
		if (point_num == max_number)
		{
			Point3D*temp = p;                //若点数超过初始最大容纳量，申请二倍空间存点
			max_number *= 2;
			p = new Point3D[max_number];

			int j = 0;
			while (j < point_num)
			{                                    //将已写入点赋到新内存中
				p[j] = temp[j];
				j++;
			}
			delete[] temp;
		}

		i++;
	}
	point_num--;
	return 1;


}
