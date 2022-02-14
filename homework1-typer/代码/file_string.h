#pragma once
#ifndef _FILE_STRING_
#define _FILE_STRING_
#include<iostream>

class String
{
private:
    std::string str_content;
    int line_num;

public:
    String* next_str = nullptr;
    String* preror_str = nullptr;
    String(std::string str_input);
    String() { str_content = "none"; };
    ~String();

    std::string GetContent() { return this->str_content; };
    int GetLineNum() { return this->line_num; };

    int FindSubStringPos(std::string sub_string, int pLen);//Ѱ�����ַ���
    void SetStringContent(std::string str) { str_content = str; };//�滻�����ַ���
    void SetLineNum(int num) { line_num = num; };//�ı��ַ�����������
};

#endif // !_FILE_STRING_