#include "file_string.h"
#include "File_linklist.h"
#include "Functions.h"
#include <fstream>

std::string in_name, out_name;
std::fstream InputTXT;
std::fstream OutputTXT;
FileLinklist Linklist;//����
int exit_sign = 0;//�˳�ѡ��ģʽ���ź�


/// <summary>
/// ����ļ��Ƿ����
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
inline bool FileExists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

void Start()
{
	/// <summary>
	/// �������ļ��ļ��
	/// </summary>
	std::cout << "please input the name of in_txt: ";
	std::cin >> in_name;
	std::cout << std::endl;
	std::ifstream InputTXT(in_name, std::ios::in);
	std::ifstream InputTXT_without_txt(in_name + ".txt", std::ios::in);
	if (!InputTXT) //����Ƿ���ڸ��ļ�
	{
		if (!InputTXT_without_txt) {
			std::cout << "wrong name,please check it" << std::endl;
			exit(0);
		}
		else {
			in_name = in_name + ".txt";
		}
	}


	/// <summary>
	/// ��������ļ��ļ��
	/// </summary>
	std::cout << "please input the name of out_txt: ";
	std::cin >> out_name;
	std::fstream OutTXT(out_name, std::ios::in);
	std::fstream OutTXT_without_txt(out_name + "txt", std::ios::in);
	if (!FileExists(out_name) && !FileExists(out_name + ".txt")) //����Ƿ���ڸ��ļ�
	{
		char answer;//���ش�
		int flag = 0;//���ѭ��
		std::string has_txt;
		if (out_name.length() <= 4) 
		{
			has_txt = "no txt suffix";//����С��4�����޺�׺
		}
		else 
		{
			has_txt = out_name.substr(out_name.length() - 4, out_name.length());//����ַ�����λ�Ƿ���txt
		}

		std::cout << "maybe wrong name,please check it" << std::endl;
		std::cout << "want to create new one using this name?(y/n)    ";
		std::cin >> answer;
		switch (answer)
		{
		case 'y':
			if (has_txt == ".txt")//�к�׺txt
			{
				OutputTXT.open(out_name, std::ios::out);
				OutputTXT.close();
				std::cout << "file has been created" << std::endl;
			}
			else
			{
				OutputTXT.open(out_name + ".txt", std::ios::out);
				OutputTXT.close();
				out_name = out_name + ".txt";
				std::cout << "file has been created" << std::endl;
			}
			flag = 1;
			break;
		case 'n':
			std::cout << "exe will close later......" << std::endl;
			exit(0);
			break;
		default:
			flag = 1;
			break;

		}
	}
	std::cout << "...........................................Loading..........................................." << std::endl;
}

int main()
{
	Start();
	ReadFile(in_name, &Linklist);//���ļ����ݶ��뻺����
	HelpPanel();
	std::cout << "����������" << Linklist.L->GetLineNum() << std::endl << "����Ϊ��" << Linklist.L->GetContent() << std::endl;
	while (exit_sign == 0)
	{
		ChooseMode(Linklist,exit_sign);
		std::cout << "����������" << Linklist.L->GetLineNum() << std::endl << "����Ϊ��" << Linklist.L->GetContent() << std::endl;
	}
	system("pause");
	return 0;
}