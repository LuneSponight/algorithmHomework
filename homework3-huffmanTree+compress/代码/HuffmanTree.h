//
// Created by S on 2021/11/29.
//
#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H


class HuffmanTree {
public:
    int weight;//权重
    char asc;//所代表的asc码

    HuffmanTree *parent;//双亲
    HuffmanTree *leftChild;//左孩子
    HuffmanTree *rightChild;//右孩子

    HuffmanTree();//构造函数
    ~HuffmanTree();//析构函数
};

HuffmanTree::HuffmanTree() {
    weight = 0;
    asc = 'N';
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

HuffmanTree::~HuffmanTree() {
    std::cout<<"HuffmanTree has destroyed"<<std::endl;
}


#endif
