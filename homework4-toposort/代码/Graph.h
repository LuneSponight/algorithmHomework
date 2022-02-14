//
// Created by S on 2021/12/18.
//

#ifndef COURSE_GRAPH_H
#define COURSE_GRAPH_H
#include <iostream>

const int MAX_NODE_NUM = 100;

struct ArcNode{
    int VerPos = -1;//边的来源序号
    ArcNode* next = nullptr;//  → O ‘→’
};

struct VertexNode{
    std::string name;//学科名称
    int term = 0;//指定开课学期
    int score = 0;//学时
    bool isInQueue = false;//是否入队
    ArcNode* firstArc = nullptr; // → O ’→‘ →
};

class Graph {
private:
    VertexNode Nodes[MAX_NODE_NUM];//顶点表
    int InDegree[MAX_NODE_NUM];//入度
    int edgeNum;//边数
    int verNum;//顶点数

public:
    Graph(int VerNum, int ENum, VertexNode Nodes[]);
    ~Graph();
    void TopologicalSortOutput(int termReq[]);
};


#endif //COURSE_GRAPH_H
