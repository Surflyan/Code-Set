/*此程序实现了通过哈夫曼编码来压缩任意格式文件
  在一些字符串操作调用了字符操作函数倒置压缩大文件有明显的延迟
  压缩文件，生成编码本，解压后文件需要手动输入文件名，可优化为自动添加后缀和手动选择 
  以后再改。*/

//2016.12.4


#include <iostream>
#include <cstdio>
#include "huffman.h"
using namespace std;
int main()
{  	  
	char fileName[256];
	char passFileName[256];
	char compressFileName[256];
	char decompressFileName[256];

	while (1)
	{
		char select;
		cout << "\t"<<"_________________________________________" << endl;
		cout << "\t| \t\t" << "欢迎使用YJL文件压缩软件" << endl;
		cout << "\t| ◎请选择以下操作：                          |"<< endl;
		cout << "\t| 1.打开文件并对其进行解压                    |" << endl;
		cout << "\t| 2.压缩文件并译码成源文件                    |" << endl;
		cout << "\t| 3. 退出程序                                 |" << endl;
		cout << "\t" << "____________________________________________" << endl;

		select = getchar();
		getchar();
		if (select == '1')
		{
			printf("\t压缩文件名称：\n");
			gets_s(fileName);
			ReadText(fileName);
			CreatHuffmanTree();
			HuffmanCode();

			printf("\t压缩后文件名：");
			gets_s(compressFileName);
			CompressFile(fileName, compressFileName);
			printf("\t压缩完毕！\n");

			char  op;
			cout <<"\t __________________________________________" << endl;
			cout << "\t|◎请选择相关查阅功能：                   |" << endl;
			cout << "\t| 1.生成哈夫曼编码本                      |"<< endl;
			cout << "\t| 2.查看压缩率                            |" << endl;
			cout << "\t| 3.返回主界面                            |" << endl;
			cout << "\t|_________________________________________" << endl;
			op = getchar();
			getchar();
			if (op == '1')
			{
				printf("\t哈夫曼编码本名称：");
				gets_s(passFileName);
				WritePassToFile(passFileName);
				printf("\t生成完毕\n");
			}
			else if (op == '2')
			{
				float compressRate;
				compressRate = CalcCompressibility(fileName, compressFileName);
				printf("%.2f%", compressRate);
			}
			else
				;
		}
			

		else if (select == '2')
		{
			printf("\t解压文件名：");
			gets_s(fileName);
			printf("\t解压后文件名：");
			gets_s(decompressFileName);
			DecompressFile(compressFileName, decompressFileName);
			printf("\t解压完毕\n");
		}

		else
		{
			printf("\t再见!\n");
			break;
		}
	
	}

    return 0;

}