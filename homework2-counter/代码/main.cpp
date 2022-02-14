#include <iostream>
#include <cstring>
#include "Stack.h"
#include "Functions.h"

OptList OptList;
NumList NumList;

int main() {
    std::cout << "EXAMPLE: 23 * ( 123 - 6 ) #" << std::endl;
    std::cout << "please putin the expression: " << std::endl;
    char *ExpNode = new char[10];//数字大小
    std::cin >> ExpNode;//输入字符串
    while (strcmp(ExpNode, "#") != 0) {
        int type = IsNumber(ExpNode);//判断类型
        if (type == 1) {//操作符
            OperationStack *NewOptNode = new OperationStack(ExpNode[0]);

            JudgePriority(OptList, NumList, NewOptNode);//判断符号优先级以方便出栈入栈

        } else if (type == 3) {//不是规定的符号
            std::cout << "your output is not up to specification, please check it" << std::endl;
            std::cout << "WRONG INPUT:" << ExpNode << std::endl;
            exit(0);
        } else if (type == 4) {//输入为空
            std::cout << "EMPTY INPUT!!!PLEASE CHECK IT" << std::endl;
            exit(0);
        } else if (type == 5 || type == 2) {//数字，但5比较长
            int number = ToIntType(ExpNode);
            NumberStack *NewNumNode = new NumberStack(number);

            //入栈操作
            NumList.Push(NewNumNode);

        } else if (type == 6) {//浮点数
            float Float = ToFloatType(ExpNode);
            NumberStack *NewNumNode = new NumberStack(Float);

            //入栈操作
            NumList.Push(NewNumNode);

        } else {//其他情况，直接退出程序
            std::cout << "ERROR" << std::endl;
            exit(0);
        }
        std::cin >> ExpNode;
    }
    delete[] ExpNode;
    if (OptList.IsEmpty()) {//符号栈为空
        std::cout << "==" << NumList.Top->number << std::endl;
    } else {
        while (OptList.Top != OptList.Bottom) {
            float fin_a = NumList.Pop();
            float fin_b = NumList.Pop();
            float fin_result = Calculate(OptList.Top->operation, fin_a, fin_b);//计算最终结果
            NumberStack *FinTemp = new NumberStack(fin_result);
            NumList.Push(FinTemp);
            char recycleChar = OptList.Pop();
        }
        std::cout << "==" << NumList.Top->number << std::endl;
    }
}