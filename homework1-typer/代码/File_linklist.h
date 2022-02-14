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

    int Length();               //长度
    void CreatNewStr(std::string str_content); //创建新的字符串在后面
    int Character();//统计字符数
};

#endif // !_FILE_LINKLIST_
