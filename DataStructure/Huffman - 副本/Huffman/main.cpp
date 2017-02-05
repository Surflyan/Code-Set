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
		cout << "\t| \t\t" << "��ӭʹ��JLU�ļ�ѹ�����" << endl;
		cout << "\t| ����ѡ�����²�����                          |"<< endl;
		cout << "\t| 1.���ļ���������н�ѹ                    |" << endl;
		cout << "\t| 2.ѹ���ļ��������Դ�ļ�                    |" << endl;
		cout << "\t| 3. �˳�����                                 |" << endl;
		cout << "\t" << "____________________________________________" << endl;

		select = getchar();
		getchar();
		if (select == '1')
		{
			printf("\tѹ���ļ����ƣ�\n");
			gets_s(fileName);
			ReadText(fileName);
			CreatHuffmanTree();
			HuffmanCode();

			printf("\tѹ�����ļ�����");
			gets_s(compressFileName);
			CompressFile(fileName, compressFileName);
			printf("\tѹ����ϣ�\n");

			char  op;
			cout <<"\t __________________________________________" << endl;
			cout << "\t|����ѡ����ز��Ĺ��ܣ�                   |" << endl;
			cout << "\t| 1.���ɹ��������뱾                      |"<< endl;
			cout << "\t| 2.�鿴ѹ����                            |" << endl;
			cout << "\t| 3.����������                            |" << endl;
			cout << "\t|_________________________________________" << endl;
			op = getchar();
			getchar();
			if (op == '1')
			{
				printf("\t���������뱾���ƣ�");
				gets_s(passFileName);
				WritePassToFile(passFileName);
				printf("\t�������\n");
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
			printf("\t��ѹ�ļ�����");
			gets_s(fileName);
			printf("\t��ѹ���ļ�����");
			gets_s(decompressFileName);
			DecompressFile(compressFileName, decompressFileName);
			printf("\t��ѹ���\n");
		}

		else
		{
			printf("\t�ټ�!\n");
			break;
		}
	
	}

    return 0;

}