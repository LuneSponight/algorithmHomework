#include "File_linklist.h"

void FileLinklist::CreatNewStr(std::string str_content) //后接一个字符串
{
    String* Node = new String(str_content);
    Node->SetStringContent(str_content);
    if (!(head->next_str))
    {
        Node->next_str = nullptr;
        head->next_str = Node;
        Node->preror_str = head;
        tail = Node;
    }
    else
    {
        Node->next_str = nullptr;
        tail->next_str = Node;
        Node->preror_str = tail;
        tail = Node;
    }
}

int FileLinklist::Character()
{
    int char_num = 0;
    String* target = new String();
    target = head->next_str;
    while (target != NULL) {
        int space = 0;
        for (int i = 0; i < target->GetContent().length(); i++) {
            if (target->GetContent()[i] == ' ')
            {
                space++;
            }
        }
        char_num = char_num + target->GetContent().length() - space;
        target = target->next_str;
    }
    delete target;
    return char_num;
}

int FileLinklist::Length()
{
    int length = 0;
    String* target = new String();
    target = head;
    while (target != NULL) {
        length++;
        target = target->next_str;
    }
    delete target;
    return length - 1;
}