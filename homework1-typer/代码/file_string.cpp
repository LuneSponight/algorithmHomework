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
    next[0] = -1;//-1����û���ظ��Ӵ�
    int k = -1;
    for (int q = 1; q <= len; q++)
    {
        while (k > -1 && T[k + 1] != T[q])//��һ��Ԫ�ز���ȣ���k��ǰ����
        {
            k = next[k];
        }
        if (T[k + 1] == T[q])//��һ��Ԫ����ȣ�������ظ��Ӵ�+1
        {
            k = k + 1;
        }
        next[q] = k;//��next���鸳ֵ
    }
}


/// <summary>
/// KMP�㷨
/// </summary>
/// <param name="sub_string"></param>
/// <returns>-1����δ�ҵ�</returns>
int String::FindSubStringPos(std::string p, int plen)
{
	std::string s = this->GetContent();//ԭ�ַ���
	int* next = new int[plen + 10];
	GetNext(next, p, plen);
	int k = -1;
	int i = 0;
	int Slen = int(GetContent().length());
	for (; i < Slen; i++)
	{
		while (k > -1 && p[k + 1] != s[i])//������һ���ַ�����ȣ���ǰ����
		{
			k = next[k];
		}
		if (p[k + 1] == s[i])//���������ַ���ȣ�k+1��ƥ���Ӵ���һ���ַ�
		{
			k++;
		}
		if (k == plen - 1)//ƥ��ɹ������ض̴��ڳ�����λ�á�
		{
			delete[] next;
			return int(i - plen + 1);
		}
	}
	delete[] next;
	return -1;

}