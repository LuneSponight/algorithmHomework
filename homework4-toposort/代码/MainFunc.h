//
// Created by S on 2021/12/18.
//

#ifndef COURSE_MAINFUNC_H
#define COURSE_MAINFUNC_H
#include "MainFunc.cpp"
#include "Graph.h"

///开始
void Start(std::string &fileName);

///读入文件，获取要求列表，返回学科数目（节点数）
void ReadFileInStr(std::string fileName, std::string &fileStr, std::string &request, int &NodeNum);

///request转数组
void RequestToArr(std::string requestsStr, int requestsArr[8]);

///fileStr转图
void FileStrToGraph(std::string fileStr, VertexNode Nodes[], int NodeNum, int &EdgeNum);

///拓补排序并输出



#endif //COURSE_MAINFUNC_H
