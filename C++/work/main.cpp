//作为折线类的检验，

#include <iostream>
#include <fstream>
#include"Curve3D.h"

using namespace std;
int main()
{

	Point3D p1(1, 2, 3),p2(2, 3, 4), p3(4, 5, 6), p4(5, 6, 7), p5(6, 7, 8), p6(7, 8, 9), p7(8, 9, 10);

	Curve3D L1(0,0,0);
	Curve3D L2, L3, L4, L5, L6, L7;

	cout << "_________________"<<endl;
	L2 = L1 + p1;                              //添加点
	L2.display_curve();                       //输出信息
	L2.curve_len();                       //算长度

 
	cout << "_________________" << endl;
	L3 = L2 + p2;
	L4 = L3 + p4;                                     //验证点的个数超过初始折线五个的容量
	L5 = L4 + p5;
	L6 = L5 + p6;
	L7 = L6 + p7;
	L7.display_curve();
	L7.curve_len();

	cout << "_________________" << endl;
	L3 = L2 - p1;                                //删除点
	L3.display_curve();
	L4.curve_len();

	cout << "_________________" << endl;
	L4 = L3;                                   //折线的赋值
	L4.display_curve();
	L4.curve_len();

	cout << "__________________" << endl;

	ofstream ascii_file("file.txt");            //写入文本文件
	L7.write_txt(ascii_file);
	ascii_file.close();


	ifstream file2("file.txt");          //读取文本文件
	L1.read_txt(file2);
	file2.close();
	L1.display_curve();

	cout << "______________________" << endl;
	ofstream binary_fiel("binary.bin");   //写入二进制文件
	L7.write_binary(binary_fiel);
	binary_fiel.close();


	ifstream binary_read("binary.bin");    //读取二进制文件
	L2.read_binary(binary_read);
	binary_read.close();
	L2.display_curve();
}