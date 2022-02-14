//
// Created by S on 2021/11/15.
//

#ifndef PROJECTS_FUNCTIONS_H
#define PROJECTS_FUNCTIONS_H

#include <iostream>
#include <cstring>
#include <cmath>

char operators[6] = {'+', '-', '*', '/', '(', ')'};//所有操作符

int IsNumber(char *content) {//1表示操作符，2表示单个数字，3表示输入不合规范，4表示输入为空，5表示多个数字，6表示浮点数
    int floatFlag = 0;//浮点数判断
    int length = int(strlen(content));//获取输入的字符串长度

    if (length == 0) {
        std::cout << "Wrong Msg, The input is empty" << std::endl;
        return 4;
    }

    if (length == 1) {
        //是否为操作符
        for (int i = 0; i <= 5; i++) {
            if (content[0] == operators[i])
                return 1;//是操作符
        }
        //是否为单个数字
        if (content[0] >= 48 && content[0] <= 57) {
            return 2;//是数字
        } else {
            return 3;//不合规范，为其他符号
        }
    }
        //长度不为1
    else {
        if (content[0] != '-') {//正数
            for (int i = 0; i < length; i++) {
                if (content[i] < 48 || content[i] > 57) {
                    if (content[i] == '.') {
                        if (i > 0) {//不是第一个数为.
                            floatFlag++;//浮点数
                        }
                    }
                    if (floatFlag == 0)
                        return 3;//不合规范，为/* 或++03等多余符号
                }
            }
            if (floatFlag == 1)//只有一个点
                return 6;//为浮点数
            return 5;//为数字
        } else {//负数
            for (int i = 1; i < length; i++) {
                if (content[i] < 48 || content[i] > 57) {
                    if (content[i] == '.') {
                        if (i > 1) {//不是第一个数为.
                            floatFlag++;//浮点数
                        }
                    }
                    if (floatFlag == 0)
                        return 3;//不合规范，为/* 或++03等多余符号
                }
            }
            if (floatFlag == 1)//只有一个点
                return 6;//为浮点数
            return 5;//为数字
        }
    }
}

//转换为int类型
int ToIntType(char *content) {
    if (content[0] == '-') {//负数
        int realNum = 0;
        int length = int(strlen(content));
        int power = 1;
        for (int i = 1; i < length - 1; i++) {
            power *= 10;
        }
        for (int i = 1; i < length; i++) {
            realNum += power * (content[i] - 48);
            power /= 10;
        }
        return -realNum;
    } else {//正数
        int realNum = 0;
        int length = int(strlen(content));
        int power = 1;
        for (int i = 0; i < length - 1; i++) {
            power *= 10;
        }
        for (int i = 0; i < length; i++) {
            realNum += power * (content[i] - 48);
            power /= 10;
        }
        return realNum;
    }
}

float ToFloatType(char *content) {
    int pointPos = 0;
    for (int i = 0; i < strlen(content); i++) {//寻找浮点位置
        if (content[i] == '.') {
            pointPos = i;
            break;
        }
    }
    if (content[0] == '-') {//负数
        float realNum = 0;
        int length = int(strlen(content));
        float power = 1;
        for (int i = 1; i < pointPos - 1; i++) {
            power *= 10;
        }
        for (int i = 1; i < length; i++) {
            realNum += power * (content[i] - 48);
            power /= 10;
        }
        return -realNum;
    } else {//正数
        float realNum = 0;
        int length = int(strlen(content));
        float power = 1;
        for (int i = 0; i < pointPos - 1; i++) {
            power *= 10;
        }
        for (int i = 0; i < pointPos; i++) {
            realNum += power * (content[i] - 48);
            power /= 10;
        }
        for(int i = pointPos + 1; i < length;i++){
            realNum += power * (content[i] - 48);
            power /= 10;
        }
        return realNum;
    }
}

float Calculate(char op, float a, float b) {
    float result = 0;

    switch (op) {
        case '+':
            result = b + a;
            break;
        case '-':
            result = b - a;
            break;
        case '*':
            result = b * a;
            break;
        case '/':
            if (a == 0) {
                std::cerr << "divided num can not be 0。\n";
                exit(0);
            } else
                result = b / a;
            break;
        default:
            break;
    }
    return result; // 返回计算得到的结果
}

void JudgePriority(OptList &OptList, NumList &NumList, OperationStack *Node) {
    //赋予该运算符权重
    if (Node->operation == '+' || Node->operation == '-') {
        Node->weight = 1;
    } else if (Node->operation == '*' || Node->operation == '/') {
        Node->weight = 2;
    } else if (Node->operation == '(') {
        Node->weight = 0;
    } else if (Node->operation == ')') {
        Node->weight = 3;
    }

    if (Node->weight != 3 && OptList.IsEmpty()) {
        OptList.Push(Node);
        return;
    }

    if (Node->weight == 3) {//如果是右括号，重复出栈数字运算，直到出栈的是左括号
        if (OptList.IsEmpty()) {//空栈则不能是右括号
            std::cout << std::endl;
            std::cerr << "NO MATCH PARENTHESES" << std::endl;
            exit(0);
        }
        while (OptList.Top->weight != 0) {
            char stackOperator = OptList.Pop();
            float a = NumList.Pop();
            float b = NumList.Pop();
            float results = Calculate(stackOperator, a, b);
            NumberStack *Results = new NumberStack(results);
            NumList.Push(Results);
        }
        char leftParentheses = OptList.Pop();//回收左括号
        return;
    }

    if (Node->weight == 0 || Node->weight >= OptList.Top->weight) {
        OptList.Push(Node);//左括号或优先级大于等于之前的直接入栈
        return;
    }

    if (Node->weight < OptList.Top->weight) {
        while (OptList.Top != OptList.Bottom) {
            float a = NumList.Pop();
            float b = NumList.Pop();
            float results = Calculate(OptList.Top->operation, a, b);
            char recycleChar = OptList.Pop();//弹出符号
            NumberStack *Results = new NumberStack(results);
            NumList.Push(Results);
        }
        OptList.Push(Node);
        return;
    }
}


#endif //PROJECTS_FUNCTIONS_H
