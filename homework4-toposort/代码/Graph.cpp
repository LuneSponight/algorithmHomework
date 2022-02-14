//
// Created by S on 2021/12/18.
//

#include "Graph.h"
#include <iomanip>
#include <queue>

Graph::Graph(int VerNum, int ENum, VertexNode Nodes[]) {
    this->verNum = VerNum;
    this->edgeNum = ENum;
    //初始化每个节点
    for (int i = 0; i < MAX_NODE_NUM; i++) this->InDegree[i] = 0;//入度初始值设置为0
    for (int i = 0; i < MAX_NODE_NUM; i++) {
        this->Nodes[i].name = Nodes[i].name;
        this->Nodes[i].firstArc = Nodes[i].firstArc;
        this->Nodes[i].score = Nodes[i].score;
        this->Nodes[i].term = Nodes[i].term;

        //计算入度
        ArcNode *target = new ArcNode;
        target = Nodes[i].firstArc;
        while (target != nullptr) {
            this->InDegree[target->VerPos]++;//每增近一个，增加入度
            target = target->next;
        }
        delete target;

    }
}

Graph::~Graph() {}

void Graph::TopologicalSortOutput(int termReq[]) {
    std::queue<int> ZeroInDegree;//所有零入度节点
    ArcNode *hasDegree;//是否有入度

    //将零入度的点入栈,此处学期数不能为0
    for (int i = 0; i < verNum; i++) {
        while (InDegree[i] == 0 && Nodes[i].term == 0 && (!Nodes[i].isInQueue)) {
            ZeroInDegree.push(i);
            Nodes[i].isInQueue = true;
        }
    }

    //从第一学期到第八学期
    for (int i = 1; i <= 8; i++) {
        std::cout << "Courses for term " << i << ":" << std::endl;
        std::cout << "***************************************" << std::endl;
        int courseNum = termReq[i - 1];//这学期课程数

        //将要求学期的课置入
        //排除该学期必选的课
        for (int j = 0; j < verNum; j++) {
            if (Nodes[j].term == i) {
                std::cout << std::setw(15) << std::setiosflags(std::ios::left)<< Nodes[j].name  << "    "
                          << Nodes[j].score << std::endl;
                courseNum--;
            }
        }
        if (courseNum == 0) continue;

        //拓扑排序
        for (int k = 0; k < courseNum; k++) {
            int basicCourse = ZeroInDegree.front();
            ZeroInDegree.pop();

            //输出该课程
            std::cout << std::setw(15) << std::setiosflags(std::ios::left)<< Nodes[basicCourse].name  << "    "
                      << Nodes[basicCourse].score << std::endl;

            //删除相关的边,减少入度
            ArcNode *target = new ArcNode;
            target = Nodes[basicCourse].firstArc;
            while (target) {
                ArcNode *temp = new ArcNode;
                temp = target;
                //相关入度边减少
                InDegree[target->VerPos]--;
                target = target->next;
                delete temp;
            }
        }
        std::cout << std::endl;
        std::cout << "***************************************" << std::endl;


        //将零入度的点入栈,此处学期数不能为0
        for (int i = 0; i < verNum; i++) {
            while (InDegree[i] == 0 && Nodes[i].term == 0 && (!Nodes[i].isInQueue)) {
                ZeroInDegree.push(i);
                Nodes[i].isInQueue = true;
            }
        }
    }
}
