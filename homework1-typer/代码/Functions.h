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
	//��ȡ�ļ����ݵ�����
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
		/// �����Ƿ�������
		/// </summary>

	while (!InFile.eof()) {
		std::string str;
		getline(InFile, str);
		L->CreatNewStr(str);
		L->tail->SetLineNum(line++);
	}
	
	//������λָ�붨�����һ��
	L->L = L->tail;
	InFile.close();
}


/// <summary>
/// ʵ�������滻
/// </summary>
/// <param name="Linklist"></param>
void Substitute(FileLinklist& Linklist) {
	std::cout << "which line would you like to change?" << std::endl;
	int target_line;//Ҫ�ı����
	String* target = new String();//Ҫ�ı���ַ�������
	target = Linklist.head->next_str;//��ʼ����ʱ����
	std::cin >> target_line;
	std::cin.ignore();
	for (int i = 0; i < Linklist.Length() - 1; i++, target = target->next_str) {
		if (target->GetLineNum() == target_line) {
			std::cout << "please input the new content you want to change:" << std::endl;
			std::string new_content;
			getline(std::cin,new_content);
			target->SetStringContent(new_content);
			//��������ʱ���󣬷��򱨴�ɾ���������ڵ㣩
			return;
		}
	}
	std::cout << "didn't find the line,please check your input" << std::endl;
	delete target;//������ʱ����
	return;
}



/// <summary>
/// ʵ����������
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
/// ����KMP�㷨Ѱ�����ַ���
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
/// ʵ����ת
/// </summary>
/// <param name="Linklist"></param>
void LineJump(FileLinklist& Linklist) {
	std::cout << "please enter the line you want to go: " << std::endl;
	int destination;
	String* L_save = new String();
	L_save = Linklist.L;//����L��״̬
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
/// �ı���������
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
/// Ѱ�Ҳ��ı����ַ���
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
		//�滻�ַ���
		std::string new_string;
		new_string = Linklist.L->GetContent().substr(0, position);
		new_string = new_string + replace_string + Linklist.L->GetContent().substr(position + substring.length());
		Linklist.L->SetStringContent(new_string);
		std::cout << "Finished" << std::endl;
		return;
	}
}


/// <summary>
/// ɾ��һ���ڵ�
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

	//�ж������������Ƿ���Ҫɾ������
	if (Linklist.L->GetLineNum() == target_line) {
		std::cout << "the line you want to delete is where you are,please shift your location" << std::endl;
		ShiftLPointer(Linklist);
	}

	String* target = new String();
	target = Linklist.head->next_str;
	while (target != NULL) {
		if (target->GetLineNum() == target_line) {
			//ɾ���ڵ�
			if (target == Linklist.tail) {
				target->preror_str->next_str = nullptr;
				delete target;
				target = new String();
			}
			else {
				target->preror_str->next_str = target->next_str;
				target->next_str->preror_str = target->preror_str;
			}
			//���·�������
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
/// ����һ���ڵ�
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

	if (Linklist.L->GetLineNum() == target_line) {//���뵽ָ�봦
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
			//���·�������
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
	target = Linklist.head->next_str;//��ʼ��target
	String* newNode = new String(new_content);

	while (target != NULL) {
		if (target->GetLineNum() == target_line) {
			//���ӽڵ�
			target->next_str->preror_str = newNode;
			newNode->next_str = target->next_str;
			newNode->preror_str = target;
			target->next_str = newNode;
			//���·�������
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
/// �������
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
/// д������ļ�
/// </summary>
/// <param name="Linklist"></param>
void WriteToOutTXT(FileLinklist Linklist) {
	std::fstream OutTXT;
	OutTXT.open(out_name, std::ios::out | std::ios::app);
	if (!OutTXT) // �����ȡʧ�ܣ���ӡfail
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
/// ��ȡ�ļ��ɹ���־
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