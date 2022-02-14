#include"file_string.h"

String::String(std::string str_input)
{
    str_content = str_input;
}

String::~String()
{
}

void GetNext(int* next, std::string T, int len)
{
    next[0] = -1;//-1代表没有重复子串
    int k = -1;
    for (int q = 1; q <= len; q++)
    {
        while (k > -1 && T[k + 1] != T[q])//下一个元素不相等，把k向前回溯
        {
            k = next[k];
        }
        if (T[k + 1] == T[q])//下一个元素相等，所以最长重复子串+1
        {
            k = k + 1;
        }
        next[q] = k;//给next数组赋值
    }
}


/// <summary>
/// KMP算法
/// </summary>
/// <param name="sub_string"></param>
/// <returns>-1代表未找到</returns>
int String::FindSubStringPos(std::string p, int plen)
{
	std::string s = this->GetContent();//原字符串
	int* next = new int[plen + 10];
	GetNext(next, p, plen);
	int k = -1;
	int i = 0;
	int Slen = int(GetContent().length());
	for (; i < Slen; i++)
	{
		while (k > -1 && p[k + 1] != s[i])//两串下一个字符不相等，向前回溯
		{
			k = next[k];
		}
		if (p[k + 1] == s[i])//两个串的字符相等，k+1来匹配子串的一个字符
		{
			k++;
		}
		if (k == plen - 1)//匹配成功，返回短串在长串的位置。
		{
			delete[] next;
			return int(i - plen + 1);
		}
	}
	delete[] next;
	return -1;

}