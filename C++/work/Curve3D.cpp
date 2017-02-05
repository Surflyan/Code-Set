//ʵ��������ķ���
#include <iostream>
#include <math.h>
#include <fstream>
#include "Curve3D.h"

using namespace std;

Curve3D::Curve3D(double x, double y, double z)
{
	max_number = 5;
	p = new Point3D[max_number];            //��ʼ��������5������ڴ�

	p[point_num].set_x(x);             // ��ʼ�� 0��0��0
	p[point_num].set_y(y);
	p[point_num].set_z(z);

	point_num++;


}


Curve3D::Curve3D(const Curve3D &ptrline)             //�������캯�������㷵������������
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
	if (p != NULL)                  //�ͷ�������ڴ�
	{
		delete[] p;
		p = NULL;
	}

}

void Curve3D::display_curve()  const        //������������Ϣ
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
{                                                 //�������߳���
	int i = 0;                         
	double dx, dy, dz;
	double dl, length = 0;

	if (point_num == 0 || point_num == 1)
	{
		length = 0;
	}

	while (i < point_num - 1)                  //���α����󳤶�
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


Curve3D& Curve3D::operator=(Curve3D & pline)          //���ظ�ֵ�����
{


	if (pline.max_number > this->max_number)         //�ж���ֵ��������������������ǰĬ����������
	{												 //�򽫵�ǰ���ָ��ָ��������ĸ�����ڴ棬��ԭ�������ڴ��ͷţ�
		delete[]this->p;
		this->p = new Point3D[pline.max_number];
	}

	this->point_num = pline.point_num;
	this->max_number = pline.max_number;

	int i = 0;
	while (i < pline.point_num)
	{
		this->p[i] = pline.p[i];                     //���θ�ֵ
		i++;
	}

	return *this;                               //���ص�ǰ����

}



Curve3D Curve3D::operator+(Point3D &point)           //����+�����������������ӵ�
{
	Curve3D temp;                                    //��������������
	temp.point_num = this->point_num;
	if (this->max_number == this->point_num)
	{                                                //����ǰ���ߵ��Ѵ�������������������������������ӣ�
		delete[] temp.p;
		temp.p = NULL;
		temp.max_number = this->max_number * 2;
		temp.p = new Point3D[temp.max_number];
	}
	if (temp.max_number < this->max_number)
	{
		delete[]temp.p;                                  //���������������������С�ڵ�ǰ������������������������������
		temp.p = NULL;
		temp.p = new Point3D[this->max_number];
		temp.max_number = this->max_number;
	}

	int i = 0;
	while (i<point_num)
	{
		temp.p[i] = this->p[i];
		i++;                                             //���ν���ǰ���ߵ��Ҫ��ӵ�ӵ���������
	}
	temp.p[point_num] = point;

	temp.point_num++;                      //���ߵ���++

	return temp;
}


Curve3D Curve3D::operator-(Point3D & point)
{

	int i = 0;
	int flag = -1;          //��Ҫɾ���ĵ��������е��±�
	while (i < point_num)
	{
		if (p[i].get_x() == point.get_x()
			&& p[i].get_y() == point.get_y()            //���Ҵ�ɾ����
			&& p[i].get_z() == point.get_z())
		{
			flag = i;
			break;
		}
		i++;

	}
	if (flag != -1)                 //���˵�����������У�����ɾ�����������
	{
		Curve3D temp;
		temp.max_number = max_number;
		temp.point_num = point_num - 1;

		if (this->point_num > temp.max_number)
		{                                             //��Ĭ���������������浱ǰ���ߵ㣬���������ڴ�
             delete[]temp.p;
		      temp.p = NULL;
		     temp.p = new Point3D[temp.max_number];
		}
		
		i = 0;
		while (i <flag)                                  //����Ҫɾ���㣬������㸳��������
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
	else                                      //���޴˵㣬���ص�ǰ
		return *this;

}


int  Curve3D::write_txt(ofstream &os)             //д���ı��ļ�
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
{                                         //��ȡ�ı��ļ�


	int i = 0;
	double x, y, z;
	char c;
	this->point_num = 0;


	while (!in.eof())
	{
		in >> x >> c >> y >> c >> z;          //ȡ��
		p[i].set_x(x);
		p[i].set_y(y);
		p[i].set_z(z);                     //д��������
		point_num++;

		if (point_num == max_number)        //����ĵ���Ŀ������ĳ�ʼ���������
		{                                    // ��������ڴ���
			Point3D *temp = p;

			this->max_number *= 2;
			this->p = new Point3D[max_number];

			int j = 0;
			while (j < point_num)
			{
				p[j] = temp[j];               //����д�����ߵĵ����Ϣд���µĵ��ڴ�
				j++;
			}

			delete[] temp;                //�ͷ�ԭ�������ڴ�
		}
		i++;

	}
	point_num--;                    //ȥ���ȡ�ļ�ʱ���һ���ַ���Ӱ��

	return 0;

}

int Curve3D::write_binary(ofstream &os)   //д��������ļ�
{
	int i = 0;
	double x, y, z;
	while (i < this->point_num && i >= 0)
	{
		x = p[i].get_x();                    //ȡ��
		y = p[i].get_y();
		z = p[i].get_z();
		os.write((char*)& x, sizeof(double));   //д��
		os.write((char*)& y, sizeof(double));
		os.write((char*)& z, sizeof(double));
		i++;

	}
	return 0;


}

int Curve3D::read_binary(ifstream &is)           //��ȡ�������ļ�
{
	double x, y, z;
	int i = 0;
	this->point_num = 0;
	while (!is.eof())
	{
		is.read((char*)&x, sizeof(double));
		is.read((char*)&y, sizeof(double));
		is.read((char*)&z, sizeof(double));        //����

		p[i].set_x(x);
		p[i].set_y(y);                        //д����ǰ������
		p[i].set_z(z);


		this->point_num++;
		if (point_num == max_number)
		{
			Point3D*temp = p;                //������������ʼ�������������������ռ���
			max_number *= 2;
			p = new Point3D[max_number];

			int j = 0;
			while (j < point_num)
			{                                    //����д��㸳�����ڴ���
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
