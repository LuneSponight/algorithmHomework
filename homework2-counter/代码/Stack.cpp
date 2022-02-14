//
// Created on 2021/11/8.
//

#include "Stack.h"

OperationStack::OperationStack() {
    operation = '?';
    preNode = nullptr;
}

OperationStack::~OperationStack() {

}

OperationStack::OperationStack(char operation) {
    this->operation = operation;
    preNode = nullptr;
}

NumberStack::NumberStack() {
    number = 0;
    preNode = nullptr;
}

NumberStack::NumberStack(float num) {
    number = num;
    preNode = nullptr;
}

NumberStack::~NumberStack() {

}

void OptList::Push(OperationStack *Node) {
    if(Top == Bottom){//栈是否为空
        Node->preNode = Bottom;
        Top = Node;
    }else{
    Node->preNode = Top;
    Top = Node;
    }
}

char OptList::Pop(){
    if(Top != Bottom){
        char popedOpt = Top->operation;
        OperationStack* temp = Top;
        Top = Top->preNode;
        delete temp;
        temp = nullptr;
        return popedOpt;
    }else{
        std::cout<<"ERROR, THE NUMBER STACK IS EMPTY"<<std::endl;
        exit(0);
    }
}

OptList::OptList() {
    Top = new OperationStack();
    Top = nullptr;
    Bottom = Top;
}

OptList::~OptList() {
    delete Top;
    delete Bottom;
}

bool OptList::IsEmpty() {
    if (Top == Bottom)
        return true;
    else
        return false;
}

NumList::NumList() {
    Top = new NumberStack();
    Top = nullptr;
    Bottom = Top;
}

NumList::~NumList() {
    delete Top;
    delete Bottom;
}

void NumList::Push(NumberStack *Node) {
    if(Top == Bottom){//栈是否为空
        Node->preNode = Bottom;
        Top = Node;
    }else {
        Node->preNode = Top;
        Top = Node;
    }
}

float NumList::Pop() {
    if(Top != Bottom){
        float popedNum = Top->number;
        NumberStack* temp = Top;
        Top = Top->preNode;
        delete temp;
        temp = nullptr;
        return popedNum;
    }else{
        std::cout<<"ERROR, THE NUMBER STACK IS EMPTY"<<std::endl;
        exit(0);
    }
}

bool NumList::IsEmpty() {
    if(Top == Bottom)
        return true;
    else
        return false;
}
