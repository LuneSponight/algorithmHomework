#pragma once
#ifndef _FILE_LINKLIST_
#define _FILE_LINKLIST_
#include "file_string.h"

class FileLinklist
{
public:
    String* L = head;
    String* tail = head;
    String* head = new String();

    int Length();               //����
    void CreatNewStr(std::string str_content); //�����µ��ַ����ں���
    int Character();//ͳ���ַ���
};

#endif // !_FILE_LINKLIST_
