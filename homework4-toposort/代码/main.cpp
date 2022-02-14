/* 图的关键路径
 * 魏家伟
 * 2021.12.17
 * */

#include <iostream>
#include "MainFunc.h"
#include "Graph.h"

int main() {
    ///全局变量存放处
    std::string fileName;//文件名
    std::string fileContent;//文件内容
    std::string requests;//每学期要求
    int requestsArr[8] = {0};//数组每学期要求
    int NodeNum = 0;//课程数
    int EdgeNum = 0;//边数
    VertexNode Nodes[MAX_NODE_NUM];

    /////////输入数据
    Start(fileName);
    /////////将文件读入
    ReadFileInStr(fileName, fileContent, requests, NodeNum);
    /////////字符串转图,字符串转数组
    RequestToArr(requests, requestsArr);
    FileStrToGraph(fileContent, Nodes, NodeNum, EdgeNum);
    /////////图的初始化
    Graph Course(NodeNum, EdgeNum, Nodes);
    /////////拓补排序
    /////////输出
    Course.TopologicalSortOutput(requestsArr);
    return 0;
}
