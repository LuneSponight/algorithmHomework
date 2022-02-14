//
// Created on 2021/11/8.
//
#include <iostream>
#ifndef PROJECTS_STACK_H
#define PROJECTS_STACK_H

//操作符栈
class OperationStack{
private:

public:
    char operation;
    int weight;//权重,1为+-，2为*/，0为（，3为）
    OperationStack();
    OperationStack(char operation);
    ~OperationStack();
    OperationStack* preNode;
};

//数字栈
class NumberStack{
private:

public:
    float number;
    NumberStack();
    NumberStack(float num);
    ~NumberStack();
    NumberStack* preNode;
};

class OptList{
public:
    OptList();
    ~OptList();
    OperationStack* Top;
    OperationStack* Bottom;
    void Push(OperationStack* Node);
    char Pop();
    bool IsEmpty();
};

class NumList{
public:
    NumList();
    ~NumList();
    NumberStack* Top;
    NumberStack* Bottom;
    void Push(NumberStack* Node);
    float Pop();
    bool IsEmpty();
};

#endif //PROJECTS_STACK_H
