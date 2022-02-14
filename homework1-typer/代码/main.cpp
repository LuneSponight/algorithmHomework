#include "file_string.h"
#include "File_linklist.h"
#include "Functions.h"
#include <fstream>

std::string in_name, out_name;
std::fstream InputTXT;
std::fstream OutputTXT;
FileLinklist Linklist;//链表
int exit_sign = 0;//退出选择模式的信号


/// <summary>
/// 检测文件是否存在
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
	/// 对输入文件的检测
	/// </summary>
	std::cout << "please input the name of in_txt: ";
	std::cin >> in_name;
	std::cout << std::endl;
	std::ifstream InputTXT(in_name, std::ios::in);
	std::ifstream InputTXT_without_txt(in_name + ".txt", std::ios::in);
	if (!InputTXT) //检查是否存在该文件
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
	/// 对输出的文件的检测
	/// </summary>
	std::cout << "please input the name of out_txt: ";
	std::cin >> out_name;
	std::fstream OutTXT(out_name, std::ios::in);
	std::fstream OutTXT_without_txt(out_name + "txt", std::ios::in);
	if (!FileExists(out_name) && !FileExists(out_name + ".txt")) //检查是否存在该文件
	{
		char answer;//检测回答
		int flag = 0;//检测循环
		std::string has_txt;
		if (out_name.length() <= 4) 
		{
			has_txt = "no txt suffix";//长度小于4明显无后缀
		}
		else 
		{
			has_txt = out_name.substr(out_name.length() - 4, out_name.length());//检测字符串后几位是否有txt
		}

		std::cout << "maybe wrong name,please check it" << std::endl;
		std::cout << "want to create new one using this name?(y/n)    ";
		std::cin >> answer;
		switch (answer)
		{
		case 'y':
			if (has_txt == ".txt")//有后缀txt
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
	ReadFile(in_name, &Linklist);//将文件内容读入缓冲区
	HelpPanel();
	std::cout << "所在行数：" << Linklist.L->GetLineNum() << std::endl << "内容为：" << Linklist.L->GetContent() << std::endl;
	while (exit_sign == 0)
	{
		ChooseMode(Linklist,exit_sign);
		std::cout << "所在行数：" << Linklist.L->GetLineNum() << std::endl << "内容为：" << Linklist.L->GetContent() << std::endl;
	}
	system("pause");
	return 0;
}