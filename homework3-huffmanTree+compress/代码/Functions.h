//
// Created by S on 2021/11/29.
//

#ifndef HUFFMAN_FUNCTIONS_H
#define HUFFMAN_FUNCTIONS_H

#include "HuffmanTree.h"
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cmath>

void Start() {
    std::cout << "Please select the mode:" << std::endl;
    std::cout << "1: Huffman Compress" << std::endl;
    std::cout << "2: Huffman Decompress" << std::endl;
    std::cout << "3: Exit" << std::endl;
}


void SwitchMode(char &Mode) {//选择模式的检测,排除1,2,3以外的输入
    std::cin >> Mode;
    std::cout << std::endl;
    if (Mode != '1' && Mode != '2' && Mode != '3') {
        std::cerr << "Wrong Input, Please Check Your Mode" << std::endl;
    } else if (Mode == '3') {
        std::cout << "Thanks for your using" << std::endl;
        exit(1);
    }
}

void PutInFileName(std::string &inFileName, std::string &outFileName) {//将文件名字输入,查找文件是否存在

    while (true) {//输入文件
        std::cout << "please putin the origin file(include\".txt\"):" << std::endl;
        std::cin >> inFileName;
        std::fstream InFile(inFileName, std::ios::in);



        if (!InFile) {
            std::cout << "Your InFile dose not exist" << std::endl;
        } else {
            //检测文件是否为空
            char ch;
            InFile>>ch;
            if(InFile.eof()){
                std::cout<<"Your File is empty!!!!"<<std::endl;
                InFile.seekg(0,std::ios::beg);
                continue;
            }
            InFile.seekg(0,std::ios::beg);
            break;
        }
    }


    //输出文件
    std::cout << "please putin the target file(include\".txt\"):" << std::endl;
    std::cin >> outFileName;
    std::fstream OutFile(outFileName, std::ios::in);
    if (!OutFile) {
        std::cout << "Your OutFile dose not exist, we will create one later......" << std::endl;
    }
}

void StatisticChars(const std::string &strLine, int charArr[128], int charPos[128], int &length) {//统计字符数量/权重/种类

    for (char i: strLine) {//装载字符进入arr数组中的权重
        charArr[i]++;//该节点的权重加一
    }

    ///统计原来数组有符号的位置///

    for (int i = 0; i < 128; i++) {//所有可能出现的符号
        if (charArr[i] != 0) {//出现过
            charPos[length++] = i;//ASCII第i位不是空的,其他权重为0
        }
    }
    ///统计原来数组有符号的位置///

}

///寻找最小的两个叶子节点///
void SelectMin(HuffmanTree **HF, int &min1, int &min2, int nodeNum) {

    int i, j, k, l;//i表示第一个无父母的可利用的节点,j代表最小的节点,k代表非最小的第一个节点,l代表次小的节点,都是位置
    for (i = 0; i < nodeNum; i++) {
        if (HF[i]->weight != 0 && HF[i]->parent == nullptr) {//不是未被利用的节点
            min1 = i;
            break;//初始化min1
        }
    }

    for (j = 0; j < nodeNum; j++)
        if (HF[j]->weight != 0 && HF[j]->parent == nullptr)
            if (HF[j]->weight < HF[min1]->weight)
                min1 = j;


    for (k = 0; k < nodeNum; k++) {
        if (HF[k]->weight != 0 && HF[k]->parent == nullptr && min1 != k) {//非最小的第一个节点
            min2 = k;
            break;
        }
    }

    if (k >= nodeNum) {
        k = min2;
    }

    for (l = 0; l < nodeNum; l++) {
        if (HF[l]->parent == nullptr && HF[l]->weight <= HF[k]->weight && min1 != l && HF[l]->weight != 0) {
            if (HF[l]->weight <= HF[min2]->weight)
                min2 = l;
        }
    }

}

void CreatTreeGraph(HuffmanTree *HF, int level) {//画哈夫曼树

    //临界情况
    if (HF->leftChild == nullptr || HF->rightChild == nullptr) {
        for (int i = 0; i < level - 1; i++) {
            std::cout << std::setw(5) << "|";
        }
        std::cout << "---";
        std::cout << "---" << HF->weight;

        if (20 <= HF->asc && HF->asc <= 126) {
            std::cout << "  '" << HF->asc << "'" << std::endl;
        } else {
            std::cout << "  'Special Char, maybe Tab or LineFeed'" << std::endl;
        }
        return;
    }

    //左递归
    CreatTreeGraph(HF->leftChild, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << std::setw(5) << "|";
    }
    std::cout << std::endl;

    //输出数据
    for (int i = 1; i < level; i++) {
        std::cout << std::setw(5) << "|";
    }
    std::cout << "---" << HF->weight;
    std::cout << std::endl;


    //右递归
    for (int i = 0; i < level; i++) {
        std::cout << std::setw(5) << "|";
    }
    std::cout << std::endl;
    CreatTreeGraph(HF->rightChild, level + 1);

}


///获得二进制数///
void CodeHuffman(const int charPos[128], HuffmanTree *root, const int arrLen, int charHuffman[128], int huffmanCode,
                 const int charArr[128], int charHufLen[128], int level) {

    //叶子节点时
    if (root->leftChild == nullptr || root->rightChild == nullptr) {
        //寻找与weight相同的char位置
        for (int i = 0; i < arrLen; i++) {
            if (root->asc == charPos[i]) {//与该编码所在位置相同
                charHuffman[charPos[i]] = huffmanCode;
                charHufLen[charPos[i]] = level;
                return;
            }
        }
    }


    ///左子树，走0
    int temp = huffmanCode;
    int levelTemp = level;
    temp *= 2;
    levelTemp++;
    CodeHuffman(charPos, root->leftChild, arrLen, charHuffman, temp, charArr, charHufLen, levelTemp);


    ///右子树，走1
    huffmanCode = huffmanCode * 2 + 1;
    level++;
    CodeHuffman(charPos, root->rightChild, arrLen, charHuffman, huffmanCode, charArr, charHufLen, level);

}

/////////////////
////哈夫曼编码/////
void
HuffmanCompress(const int charArr[128], const int charPos[128], int arrLen, int charHuffman[128], int charHufLen[128]) {
    ///统计哈夫曼数组中权重最大的元素与最小的元素///
    int minWeight1 = 0;
    int minWeight2 = 0;

    int nodeNum = 2 * arrLen - 1;//节点数
    HuffmanTree **HF = new HuffmanTree *[nodeNum];
    for (int i = 0; i < nodeNum; i++) { HF[i] = new HuffmanTree(); }//初始化,否则调用的是野指针

    for (int i = 0; i < arrLen; i++) {
        HF[i]->weight = charArr[charPos[i]];//给weight赋值
        HF[i]->asc = (char) (charPos[i]);
    }

    for (int i = 0; i < arrLen - 1; i++) {//构建哈夫曼树

        ///寻找最小的两个叶子节点///
        SelectMin(HF, minWeight1, minWeight2, nodeNum);

        ///构建树///
        HF[arrLen + i]->weight = HF[minWeight1]->weight + HF[minWeight2]->weight;
        HF[arrLen + i]->leftChild = HF[minWeight1];
        HF[arrLen + i]->rightChild = HF[minWeight2];
        HF[minWeight1]->parent = HF[arrLen + i];
        HF[minWeight2]->parent = HF[arrLen + i];

        for (int j = 0; j < nodeNum; j++) {
            std::cout << HF[j]->weight << ",";
        }
        std::cout << std::endl;

    }

    ///画哈夫曼树////
    CreatTreeGraph(HF[nodeNum - 1], 1);

    ///开始哈夫曼编码////
    int huffmanCode = 0;//二进制编码
    int level = 0;// 行数，也是位数
    CodeHuffman(charPos, HF[nodeNum - 1], arrLen, charHuffman, huffmanCode, charArr, charHufLen, level);

    //打印哈夫曼对应编码
    for (int i = 0; i < 128; i++) {
        std::cout << "NO." << i << ":  " << (char) i << "   " << std::bitset<8>(charHuffman[i]) << "   level:"
                  << charHufLen[i] << std::endl;
    }
}

std::string IntToBin(int num) {
    std::string bin;

    if (num == 0)
        return "0";

    while (num > 0) {
        if (num % 2 == 1) {
            bin = "1" + bin;
        } else {
            bin = "0" + bin;
        }
        num /= 2;
    }

    return bin;
}

std::string IntToBinPlus0(int num, int charHufLen[128], int charPos) {
    std::string bin;

    while (num > 0) {
        if (num % 2 == 1) {
            bin = "1" + bin;
        } else {
            bin = "0" + bin;
        }
        num /= 2;
    }

    int zeroPatch;//补0,防止0110变成110
    zeroPatch = charHufLen[charPos] - bin.length();

    if (zeroPatch) {
        for (int i = 0; i < zeroPatch; i++)
            bin = "0" + bin;
    }

    return bin;
}

////二进制转整数////
int BinToInt(std::string bin) {
    int num = 0;
    int bit = 1;
    for (int i = int(bin.length() - 1); i >= 0; i--) {
        if (bin[i] == '1') {
            int power = 1;
            for (int j = 1; j < bit; j++) {
                power = 2 * power;
            }
            num = num + power;
        }
        bit++;
    }
    return num;
}

void
WriteInOutFile(const std::string &outFileName, int charHuffman[128], const int charPos[128], int arrLen,
               int charHufLen[128], int charArr[128],
               const std::string &fileContent, int &fileLen) {

    //文件流
    std::fstream OutFile;
    OutFile.open(outFileName, std::ios::out | std::ios::ate);

    std::string BITS;//转换为的二进制
    std::string TreeInfo;//树的信息

    for (char i: fileContent) {
        for (int j = 0; j < arrLen; j++)
            if (int(i) == charPos[j]) {
                std::string bit;
                bit = IntToBinPlus0(charHuffman[charPos[j]], charHufLen, charPos[j]);
                BITS += bit;
                break;
            }
    }

    std::cout << BITS << std::endl;

    unsigned char zippedChar;
    int wordNum = BITS.length() / 8;
    std::string abandonStr = BITS.substr(wordNum * 8);

    //储存长度
    OutFile << abandonStr << " ";

    //////八位压缩 哈夫曼树 + 正文 + 补齐
    //写入哈夫曼树字典
    OutFile << arrLen << " ";
    for (int i = 0; i < 128; i++) {
        if (charHufLen[i] != 0) {
            OutFile << i << " " << charArr[i] << " ";
        }
    }


    for (int i = 0; i < wordNum; i++) {
        zippedChar = BinToInt(BITS.substr(i * 8, 8));
        OutFile << zippedChar;
    }

    OutFile.close();

    fileLen = wordNum + abandonStr.length();

}


////字符串转整数////
int ToIntType(std::string content) {
    int realNum = 0;
    int length = int(content.length());
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

std::string ToBinaryTest1(std::string code) {
    std::string RES = "";
    int tem;
    for (int k = 0; k < code.length() - 1; k++) {
        char i = code[k];
        std::string res;
        bool isNeg = false;//是否为负数

        tem = (int) i;

        if (tem < 0)
            isNeg = true;

        for (int j = 0; j < 8; j++) {
            if (tem != 0) {
                if (tem % 2 == 0) {
                    res = '0' + res;
                } else {
                    res = '1' + res;
                }
                tem /= 2;
            } else {//tem == 0
                res = '0' + res;
            }
        }

        if (isNeg) {
            //取反
            for (int i = 0; i < 8; i++) {
                if (res[i] == '0') {
                    res[i] = '1';
                } else {
                    res[i] = '0';
                }
            }

            //加一
            int plusRes = BinToInt(res) + 1;
            res = IntToBin(plusRes);
        }
        RES += res;
    }
    return RES;
}


////解码--读文件///
void ReadInOutFile(std::string fileContent, int charArr[128], int charPos[128], int &arrLen, int &textPos,
                   std::string &abandonBin) {

    int pos = 0;//fileContent的位置
    //读取最后几位不足八位的二进制码
    for (int i = 0; fileContent[i] != ' '; i++) {
        abandonBin += fileContent[i];
        pos++;
    }

    pos += 1;//pos位于有效ascii码处

    //读取树---有效ascii码种类
    std::string num;

    for (int i = pos; fileContent[i] != ' '; i++) {
        num += fileContent[i];
        pos++;
    }
    arrLen = ToIntType(num);

    //现在pos处于第一个空格处
    //读取树---ascii码与权
    int spaceNum = 0;//剩余空格的数量
    bool firstFlag = true;//空格标识，用于辨认第一和第二空格
    int ranker = 0;//charPos下标

    std::string asc;//asc码的值
    std::string weight;//权

    for (int i = pos + 1; spaceNum < arrLen * 2; i++) {//开始时i=第一个空格后的第一位


        if (fileContent[i] == ' ' && firstFlag) {//asc

            charPos[ranker] = ToIntType(asc);//将asc码录入charPos
            asc = "";// 重置asc
            spaceNum++;
            firstFlag = false;//下一个为第二空格

        } else if (fileContent[i] == ' ' && !firstFlag) {//weight

            charArr[charPos[ranker]] = ToIntType(weight);
            ranker++;
            weight = "";// 重置weight
            spaceNum++;
            firstFlag = true;//下一个为第一空格

        } else if (fileContent[i] != ' ' && firstFlag) {

            asc += fileContent[i];

        } else if (fileContent[i] != ' ' && !firstFlag) {

            weight += fileContent[i];
        }

        pos++;
    }


    std::cout << "HUFFMAN TREE KEYWORDS:" << std::endl;
    for (int i = 0; i < arrLen; i++) {
        std::cout << "NO." << charPos[i] << ":  ";
        std::cout  << (char) charPos[i] << ":" << charArr[charPos[i]] << std::endl;
    }

    //////此时pos位于正文前第一个空格处
    textPos = pos + 1;//正文自然在pos+1处
}

////字符串转二进制////
std::string ToBinaryTest(std::string code) {
    std::string res;
    for (int i = 0; i < code.length(); i++) {
        res += IntToBin(code[i]);
    }
    return res;
}


void ThreadHuffman(HuffmanTree *root, std::string &realContent, std::string BINS, int &i) {

    //叶子节点，结束递归
    if (root->leftChild == nullptr || root->rightChild == nullptr) {
        realContent += root->asc;
        std::cout << root->asc;
        return;
    }

    //左子树
    if (BINS[i] == '0') {
        i++;
        ThreadHuffman(root->leftChild, realContent, BINS, i);
    } else if (BINS[i] == '1') {
        //右子树
        i++;
        ThreadHuffman(root->rightChild, realContent, BINS, i);
    }
}


//////哈夫曼解码///////
void HuffmanDecompress(int charArr[128], int charPos[128], std::string &realContent, std::string &fileContent,
                       const int textPos, const int arrLen, const std::string abandonBin) {

    std::string TEXT;
    std::string BINS;//二进制化的文本
    //读入未解读的文本
    TEXT = fileContent.substr(textPos);//此时TEXT包含'\n'，需要去掉最后一位

    ///统计哈夫曼数组中权重最大的元素与最小的元素///
    int minWeight1 = 0;
    int minWeight2 = 0;

    int nodeNum = 2 * arrLen - 1;//节点数
    HuffmanTree **HF = new HuffmanTree *[nodeNum];
    for (int i = 0; i < nodeNum; i++) { HF[i] = new HuffmanTree(); }//初始化,否则调用的是野指针

    for (int i = 0; i < arrLen; i++) {
        HF[i]->weight = charArr[charPos[i]];//给weight赋值
        HF[i]->asc = (char) (charPos[i]);
    }

    for (int i = 0; i < arrLen - 1; i++) {//构建哈夫曼树

        ///寻找最小的两个叶子节点///
        SelectMin(HF, minWeight1, minWeight2, nodeNum);

        ///构建树///
        HF[arrLen + i]->weight = HF[minWeight1]->weight + HF[minWeight2]->weight;
        HF[arrLen + i]->leftChild = HF[minWeight1];
        HF[arrLen + i]->rightChild = HF[minWeight2];
        HF[minWeight1]->parent = HF[arrLen + i];
        HF[minWeight2]->parent = HF[arrLen + i];

        for (int j = 0; j < nodeNum; j++) {
            std::cout << HF[j]->weight << ",";
        }
        std::cout << std::endl;

    }

    ///画哈夫曼树////
    CreatTreeGraph(HF[nodeNum - 1], 1);


    ///开始解码///

    BINS = ToBinaryTest1(TEXT) + abandonBin;
    std::cout << std::endl;

    //开始使用哈夫曼树
    for (int i = 0; i < BINS.length();) {
        ThreadHuffman(HF[nodeNum - 1], realContent, BINS, i);
    }
}

//////
void WriteInDecodeFile(std::string fileName, std::string realContent) {
    std::fstream FileOut;
    FileOut.open(fileName, std::ios::out | std::ios::ate);
    FileOut << realContent;
    FileOut.close();
}


#endif //HUFFMAN_FUNCTIONS_H
