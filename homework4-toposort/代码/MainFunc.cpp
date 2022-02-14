//
// Created by S on 2021/12/18.
//

#include "MainFunc.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <cmath>

void ReadFileInStr(std::string fileName, std::string &fileStr, std::string &requests, int &NodeNum) {
    std::fstream InFile(fileName, std::ios::in);//文件名
    bool WrongInput = true;//循环标志

    while (WrongInput) {
        if (!InFile) {//文件打不开
            std::cerr << "DIDNT FIND THE FILE" << std::endl;
            exit(0);
        } else {//文件打得开

            //检测文件是否为空
            char ch;
            InFile >> ch;
            if (InFile.eof()) {
                std::cout << "Your File is empty!!!!" << std::endl;
                InFile.seekg(0, std::ios::beg);
                continue;
            }
            InFile.seekg(0, std::ios::beg);//拨回指针


            //读入文件
            while (!InFile.eof()) {//文件不为空
                std::string fileLine;
                getline(InFile, fileLine);

                //判断是否为注释行
                if (fileLine[0] == '/' && fileLine[1] == '/')
                    continue;

                //是否为要求行
                if (fileLine[0] != 'c') {
                    requests += fileLine;
                    continue;
                }

                fileStr += fileLine;
                fileStr += '\n';
                NodeNum++;
            }
            WrongInput = false;
        }
    }
}

void Start(std::string &fileName) {
    std::cout << "Please putin the file you want to sort: " << std::endl;
    std::cin >> fileName;
}

void RequestToArr(std::string requestsStr, int requestsArr[8]) {

    static int round = 1;
    int pos = 0;//数组位置

    for (char i: requestsStr) {
        int num = 0;

        if (i == '\n')//到了行尾
            return;

        if (i <= '9' && i >= '1') {
            num = i - 48;//还原数据
            for (int j = 1; j < round; j++) {
                num *= 10;
            }
            requestsArr[pos] = num;
            if (pos != 8) pos++;
        }
    }
}


void FileStrToGraph(std::string fileStr, VertexNode Nodes[], int NodeNum, int &EdgeNum) {
    static int strPos = 0;
    //从第一步遍历到最后一步
    for (int i = 0; i < NodeNum; i++) {
        //先跳过前面的cxx
        while (fileStr[strPos] != '\t') strPos++;
        //再跳过空格
        while (fileStr[strPos] == '\t') strPos++;
        //录入名字
        while (fileStr[strPos] != '\t') {
            Nodes[i].name += fileStr[strPos];
            strPos++;
        }
        //再跳过空格
        while (fileStr[strPos] == '\t') strPos++;
        //录入学时
        while (fileStr[strPos] != '\t') {
            Nodes[i].score += fileStr[strPos] - 48;
            strPos++;
        }
        //再跳过空格
        while (fileStr[strPos] == '\t') strPos++;
        //录入指定开课学期
        while (fileStr[strPos] <= '9' && fileStr[strPos] >= '0') {
            Nodes[i].term += fileStr[strPos] - 48;
            strPos++;
        }
        //判断是否该换行？（是否存在下一行）
        while (fileStr[strPos] == '\t' || fileStr[strPos] == ' ') strPos++;//跳过\t
        if (fileStr[strPos] == '\n') {
            if (i < NodeNum - 1)//是否为最后一个
                strPos++;
            continue;//直接进行下一循环
        }
        //没换行则录入与之相关的节点
        //此处处理cxx
        while (fileStr[strPos] != '\n') {
            if (fileStr[strPos] == 'c') {//需要条件
                std::string edge;
                strPos++;

                while (fileStr[strPos] <= '9' && fileStr[strPos] >= '0') {//是数字
                    edge += fileStr[strPos];
                    strPos++;
                }

                //字符串转数字
                int courseCode = 0;
                for (int j = edge.length(); j > 0; j--) {
                    courseCode += int((edge[j - 1] - 48) * pow(10, edge.length() - j));
                }

                if (Nodes[courseCode - 1].firstArc == nullptr) {//该节点还没有链接的
                    ArcNode *firstArc = new ArcNode;
                    firstArc->VerPos = i;//给边赋值
                    firstArc->next = nullptr;
                    Nodes[courseCode - 1].firstArc = firstArc;//为该结点链接
                    EdgeNum++;//统计边
                } else {//该节点已经链接了
                    ArcNode *lastArc = new ArcNode;
                    lastArc->VerPos = i;
                    //创造临时指针
                    ArcNode *target = new ArcNode;
                    target = Nodes[courseCode - 1].firstArc;
                    //找到链表尾
                    while (target->next != nullptr) target = target->next;
                    //将这个节点贴到链表尾
                    target->next = lastArc;
                    EdgeNum++;//统计边
                }
            } else {//不是c开头
                strPos++;
            }
        }
    }
}
