#include <iostream>
#include <string>
#include "Functions.h"


char Mode;//模式
std::string inFileName;//读取文件
std::string outFileName;
std::string fileContent;//文件所有内容

int main() {
    while (true) {
        Start();//开始

        SwitchMode(Mode);//输入模式

        PutInFileName(inFileName, outFileName);//输入文件名称,检验文件是否存在,将文件载入缓冲区

        //按行读取字符串
        std::fstream InFile(inFileName, std::ios::in | std::ios::binary);//获取文件信息

        while (!InFile.eof()) {

            std::string strLine;//字符串

            getline(InFile, strLine);//读取字符串

            fileContent += strLine + "\n";//拼接字符串,为文件内容

        }

        //////主要程序//////
        if (Mode == '1') {//哈夫曼编码

            int charArr[128] = {0}; //Arr数组种子,可以生成哈夫曼树,位置的数字代表了符号的ASCII码
            int charPos[128] = {0};//在数组中有字符的地方
            int charHuffman[128] = {0};//对应字符的哈夫曼编码
            int charHufLen[128] = {0};//对应的哈夫曼编码长度
            int arrLen = 0;//字符种类
            int fileLen = 0;//计算压缩率


            StatisticChars(fileContent, charArr, charPos, arrLen);//统计字符数量,计算它们的权重,并确定它们在ASCII码中的位置,统计种类

            HuffmanCompress(charArr, charPos, arrLen, charHuffman, charHufLen);//哈夫曼编码

            WriteInOutFile(outFileName, charHuffman, charPos, arrLen, charHufLen, charArr, fileContent,
                           fileLen);//写入输出文件

            std::cout << "compressibility" << fileLen * 100 / fileContent.length() << "%" << std::endl;

            fileContent = "";

        } else if (Mode == '2') {//哈夫曼解码


            int charPos[128] = {0};//在数组中有字符的地方
            int charArr[128] = {0};//Arr数组种子,可以生成哈夫曼树,位置的数字代表了符号的ASCII码
            int arrLen = 0;
            int textPos = 0;//正文开始位置
            std::string abandonBin;//最后几位01串
            std::string realContent;//翻译后的文本


            ReadInOutFile(fileContent, charArr, charPos, arrLen, textPos, abandonBin);

            HuffmanDecompress(charArr, charPos, realContent, fileContent, textPos, arrLen, abandonBin);//哈夫曼解码

            WriteInDecodeFile(outFileName, realContent);

            fileContent = "";
        }

    }
}