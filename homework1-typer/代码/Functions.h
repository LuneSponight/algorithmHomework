#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "File_linklist.h"

const int GET_LINE_ARRAY_RANGE = 100;

extern std::string out_name;
char getline_array[GET_LINE_ARRAY_RANGE];

void ReadFile(std::string file_name, FileLinklist* L)
{
	std::ifstream InFile;
	InFile.open(file_name, std::ios::in);
	if (!InFile.is_open())
	{
		std::cout << "************************NOT EXIST***********************" << std::endl;
		std::cout << "Failed to open this file, please check your file is not empty." << std::endl;
		system("pause");
		InFile.close();
		exit(0);
	}
	//读取文件内容到链表
	int line = 0;
	std::cout << "We are checking if your file is empty" << std::endl;
	char is_empty;
	InFile >> is_empty;
	if (InFile.eof()) {
		std::cout << "*****************EMPTY************************" << std::endl;
		std::cout << "*****************ILLEGAL********************" << std::endl;
		std::cout << "Failed to open this file, please check your file is not empty." << std::endl;
		std::cout << "Want to Continue?(y/n)" << std::endl;
		char want_continue;
		std::cin >> want_continue;
		bool flag = 0;
		while (flag == 0) {
			std::string str;
			switch (want_continue) {
			case 'y':
				flag = 1;
				InFile.seekg(0, std::ios::beg);
				getline(InFile, str);
				L->CreatNewStr(str);
				L->tail->SetLineNum(line++);
				break;
			case 'n':
				InFile.close();
				exit(0);
				break;
			default:
				std::cout << "wrong put, please check it again" << std::endl;
				break;
			}
		}
	}
	else {
		std::cout << "your file is not empty" << std::endl;
	}
	InFile.seekg(0, std::ios::beg);

		/// <summary>
		/// 无论是否有内容
		/// </summary>

	while (!InFile.eof()) {
		std::string str;
		getline(InFile, str);
		L->CreatNewStr(str);
		L->tail->SetLineNum(line++);
	}
	
	//将链表定位指针定在最后一行
	L->L = L->tail;
	InFile.close();
}


/// <summary>
/// 实现内容替换
/// </summary>
/// <param name="Linklist"></param>
void Substitute(FileLinklist& Linklist) {
	std::cout << "which line would you like to change?" << std::endl;
	int target_line;//要改变的行
	String* target = new String();//要改变的字符串对象
	target = Linklist.head->next_str;//初始化临时对象
	std::cin >> target_line;
	std::cin.ignore();
	for (int i = 0; i < Linklist.Length() - 1; i++, target = target->next_str) {
		if (target->GetLineNum() == target_line) {
			std::cout << "please input the new content you want to change:" << std::endl;
			std::string new_content;
			getline(std::cin,new_content);
			target->SetStringContent(new_content);
			//不销毁临时对象，否则报错（删除了整个节点）
			return;
		}
	}
	std::cout << "didn't find the line,please check your input" << std::endl;
	delete target;//销毁临时对象
	return;
}



/// <summary>
/// 实现内容显现
/// </summary>
/// <param name="Linklist"></param>
void View(FileLinklist Linklist) {
	String* target = new String();
	int length = Linklist.Length() - 1;
	target = Linklist.head->next_str;
	while (target != nullptr) {
		std::cout << target->GetContent() << std::endl;
		target = target->next_str;
	}
	delete target;
}


/// <summary>
/// 利用KMP算法寻找子字符串
/// </summary>
/// <param name="Linklist"></param>
void FindSubString(FileLinklist& Linklist) {
	std::string substring;
	std::cout << "putin the substring you want to find:" << std::endl;
	std::cin.ignore();
	getline(std::cin,substring);
	size_t pLen = substring.length();
	int position = Linklist.L->FindSubStringPos(substring, pLen);
	if (position == -1) {
		std::cout << "No matching substring" << std::endl;
		return;
	}
	else {
		std::cout << Linklist.L->GetContent() << std::endl;
		for (int i = 0; i < position; i++)
			std::cout << " ";
		for (int i = 0; i < substring.length(); i++)
			std::cout << "^";
		std::cout << std::endl;
		return;
	}
}


/// <summary>
/// 实现跳转
/// </summary>
/// <param name="Linklist"></param>
void LineJump(FileLinklist& Linklist) {
	std::cout << "please enter the line you want to go: " << std::endl;
	int destination;
	String* L_save = new String();
	L_save = Linklist.L;//保存L的状态
	std::cin >> destination;
	for (Linklist.L = Linklist.head->next_str; Linklist.L != NULL;) {
		if (Linklist.L->GetLineNum() == destination) {
			std::cout << "your position has changed" << std::endl;
			return;
		}
		Linklist.L = Linklist.L->next_str;
	}
	std::cout << "wrong line, please check your input." << std::endl;
	Linklist.L = L_save;
	return;
}


/// <summary>
/// 改变所在行数
/// </summary>
/// <param name="Linklist"></param>
void ShiftLPointer(FileLinklist& Linklist) {
	int wrong_putin = 1;
	while (wrong_putin == 1) {
		std::cout << "please putin where your pointer want to go('p' stand for 'preror','n' stand for 'next'):" << std::endl;
		char c;
		std::cin >> c;
		switch (c) {
		case 'p':
			if (Linklist.L == Linklist.head->next_str) {
				std::cout << "YOU CANNOT GO FAR MORE!" << std::endl;
				break;
			}
			Linklist.L = Linklist.L->preror_str;
			wrong_putin = 0;
			break;
		case 'n':
			if (Linklist.L == Linklist.tail) {
				std::cout << "YOU CANNOT GO FAR MORE!" << std::endl;
				break;
			}
			Linklist.L = Linklist.L->next_str;
			wrong_putin = 0;
			break;
		default:
			std::cout << "please check you have putin correct character" << std::endl;
			break;
		}
	}
}


/// <summary>
/// 寻找并改变子字符串
/// </summary>
/// <param name="Linklist"></param>
void ChangeSubString(FileLinklist& Linklist) {
	std::string substring, replace_string;
	std::cout << "putin the substring you want to change:" << std::endl;
	std::cin.ignore();
	getline(std::cin, substring);
	std::cout << "putin the new content to replace:" << std::endl;
	getline(std::cin, replace_string);
	int pLen = substring.length();
	int position = Linklist.L->FindSubStringPos(substring, pLen);
	if (position == -1) {
		std::cout << "No matching substring" << std::endl;
		return;
	}
	else {
		//替换字符串
		std::string new_string;
		new_string = Linklist.L->GetContent().substr(0, position);
		new_string = new_string + replace_string + Linklist.L->GetContent().substr(position + substring.length());
		Linklist.L->SetStringContent(new_string);
		std::cout << "Finished" << std::endl;
		return;
	}
}


/// <summary>
/// 删除一个节点
/// </summary>
/// <param name="Linklist"></param>
void DeleteLine(FileLinklist& Linklist) {
	if (Linklist.head->next_str == Linklist.tail) {
		std::cout << "***********************EMPTY**************************" << std::endl;
		return;
	}
	std::cout << "please putin the line you want to delete" << std::endl;
	int target_line;
	std::cin >> target_line;

	//判断现在所在行是否处于要删除的行
	if (Linklist.L->GetLineNum() == target_line) {
		std::cout << "the line you want to delete is where you are,please shift your location" << std::endl;
		ShiftLPointer(Linklist);
	}

	String* target = new String();
	target = Linklist.head->next_str;
	while (target != NULL) {
		if (target->GetLineNum() == target_line) {
			//删除节点
			if (target == Linklist.tail) {
				target->preror_str->next_str = nullptr;
				delete target;
				target = new String();
			}
			else {
				target->preror_str->next_str = target->next_str;
				target->next_str->preror_str = target->preror_str;
			}
			//重新分配行数
			int lineNum = 0;
			for (target = Linklist.head->next_str; target != NULL; target = target->next_str, lineNum++) {
				target->SetLineNum(lineNum);
			}
			delete target;
			return;
		}
		target = target->next_str;
	}
	std::cout << "Wrong line number, please check it again" << std::endl;
	delete target;
	return;
}


/// <summary>
/// 插入一个节点
/// </summary>
/// <param name="Linklist"></param>
void InsertContent(FileLinklist& Linklist) {
	std::cout << "please putin the line you want to insert(the origin line will put off)" << std::endl;
	int target_line;
	std::cin >> target_line;
	std::cin.ignore();
	std::cout << "please putin the content for the new string" << std::endl;
	std::string new_content;
	getline(std::cin, new_content);

	if (Linklist.L->GetLineNum() == target_line) {//插入到指针处
		if(Linklist.L != Linklist.tail)
			Linklist.L = Linklist.L->next_str;
		else {
			String* NewNode = new String(new_content);
			String* target = new String();
			NewNode->preror_str = Linklist.L->preror_str;
			Linklist.L->preror_str->next_str = NewNode;
			NewNode->next_str = Linklist.L;
			Linklist.L->preror_str = NewNode;
			Linklist.L->next_str = NULL;
			Linklist.tail = Linklist.L;
			//重新分配行数
			int lineNum = 0;
			for (target = Linklist.head->next_str; target != NULL; target = target->next_str, lineNum++) {
				target->SetLineNum(lineNum);
			}
			delete target;
			return;
			return;
		}
	}

	String* target = new String();
	target = Linklist.head->next_str;//初始化target
	String* newNode = new String(new_content);

	while (target != NULL) {
		if (target->GetLineNum() == target_line) {
			//连接节点
			target->next_str->preror_str = newNode;
			newNode->next_str = target->next_str;
			newNode->preror_str = target;
			target->next_str = newNode;
			//重新分配行数
			int lineNum = 0;
			for (target = Linklist.head->next_str; target != NULL; target = target->next_str, lineNum++) {
				target->SetLineNum(lineNum);
			}
			delete target;
			return;
		}
		target = target->next_str;
	}
	std::cout << "Wrong line number, please check it again" << std::endl;
	delete target;
	return;
}

/// <summary>
/// 帮助面板
/// </summary>
void HelpPanel() {
	std::cout << "please choose the mods you want:" << std::endl;
	std::cout << " 'b' or 'begin' : Jump to the beginning" << std::endl;
	std::cout << " 'c' or 'change' : Change a substring of the content" << std::endl;
	std::cout << " 'd' or 'delete' : Delete a line" << std::endl;
	std::cout << " 'e' or 'end' : Jump to the end" << std::endl;
	std::cout << " 'f' or 'find' : Find a substring in this line" << std::endl;
	std::cout << " 'g' or 'go' : Jump to Any line" << std::endl;
	std::cout << " 'h' or 'help' : Give help" << std::endl;
	std::cout << " 'i' or 'insert' : Insert a string" << std::endl;
	std::cout << " 'l' or 'length' : Count the Number of Words and the Number of Lines" << std::endl;
	std::cout << " 'n' or 'next' : Navigate to the next line" << std::endl;
	std::cout << " 'p' or 'prior' : Navigate to the prior line" << std::endl;
	std::cout << " 'q' or 'quit' : Exit the program" << std::endl;
	std::cout << " 's' or 'substitute' : Replace any content of a line" << std::endl;
	std::cout << " 'v' or 'view' : List all lines" << std::endl;
	std::cout << " 'w' or 'write' : Write datas in your out_file" << std::endl;
}


/// <summary>
/// 写入输出文件
/// </summary>
/// <param name="Linklist"></param>
void WriteToOutTXT(FileLinklist Linklist) {
	std::fstream OutTXT;
	OutTXT.open(out_name, std::ios::out | std::ios::app);
	if (!OutTXT) // 如果读取失败，打印fail
	{
		std::cerr << "fail to open the file" << std::endl;
		return;
	}
	String* target = new String();
	target = Linklist.head->next_str;
	while (target != NULL) {
		OutTXT << target->GetContent() << std::endl;
		target = target->next_str;
	}
	OutTXT.close();
}


/// <summary>
/// 读取文件成功标志
/// </summary>
void Read() {
	std::cout << "you have read the file in the buffer" << std::endl;
}



void ChooseMode(FileLinklist& Linklist, int& exit_sign)
{
	std::string choice;
	std::cout << "enter your choice:" << std::endl;
	std::cin >> choice;

	if (choice == "b" || choice == "begin") {
		Linklist.L = Linklist.head->next_str;
	}
	else if (choice == "c" || choice == "change") {
		ChangeSubString(Linklist);
	}
	else if (choice == "d" || choice == "delete") {
		DeleteLine(Linklist);
	}
	else if (choice == "e" || choice == "end") {
		Linklist.L = Linklist.tail;
	}
	else if (choice == "f" || choice == "find") {
		FindSubString(Linklist);
	}
	else if (choice == "g" || choice == "go") {
		LineJump(Linklist);
	}
	else if (choice == "h" || choice == "help") {
		HelpPanel();
	}
	else if (choice == "i" || choice == "insert") {
		InsertContent(Linklist);
	}
	else if (choice == "l" || choice == "length") {
		std::cout << "line numbers:"<< Linklist.Length() << std::endl;
		std::cout << "characters numbers:" << Linklist.Character() << std::endl;
	}
	else if (choice == "n" || choice == "next") {
		if (Linklist.L->next_str == NULL) {
			std::cout << "out of range!!!" << std::endl;
		}
		else {
			Linklist.L = Linklist.L->next_str;
		}
	}
	else if (choice == "p" || choice == "prior") {
		if (Linklist.L->preror_str == NULL) {
			std::cout << "out of range!!!" << std::endl;
		}
		else {
			Linklist.L = Linklist.L->preror_str;
		}
	}
	else if (choice == "q" || choice == "quit") {
		exit_sign = 1;
		std::cout << "thanks for your using" << std::endl;
	}
	else if (choice == "r" || choice == "read") {
		Read();
	}
	else if (choice == "s" || choice == "substitute") {
		Substitute(Linklist);
	}
	else if (choice == "v" || choice == "view") {
		View(Linklist);
	}
	else if (choice == "w" || choice == "write") {
		WriteToOutTXT(Linklist);
	}
	else {
		std::cout << "wrong command, please putin again" << std::endl;
	}
}