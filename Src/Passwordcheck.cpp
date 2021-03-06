/*题目描述

密码要求:
1.长度超过8位
2.包括大小写字母.数字.其它符号,以上四种至少三种
3.不能有相同长度超2的子串重复
说明:长度超过2的子串
输入描述:
一组或多组长度超过2的子符串。每组占一行
输出描述:
如果符合要求输出：OK，否则输出NG
示例1
输入
021Abc9000
021Abc9Abc1
021ABC9000
021$bc9000
输出
OK
NG
NG
OK*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#define PASSWD_NG	"NG"
#define PASSWD_OK	"OK"
#define DEBUG_INFO	0
typedef struct __SUB_STRING_POS
{
	int s;//start，子串起始位
	int e;//end，子串结束位
}ST_SubStringPos,*pST_SubStringPos;
//寻找字符串中是否有重复子串长度大于RepeatLen
bool FindRepeatStr(string SrcStr,int RepeatLen)
{
	int i = 0, j = 0, m = 0;
#if DEBUG_INFO
	cout << "===================================="<< endl;
	cout  << SrcStr << endl;
#endif
	for (i = 0; i < (SrcStr.size()-1); i++)
	{
		m = i;
		for (j = i + 1; j < SrcStr.size(); j++)
		{
			if (SrcStr[m] == SrcStr[j])
			{
				m++;
			}
			else
			{
				if ((m - i) > RepeatLen)
				{//重复子串大于RepeatLen
#if DEBUG_INFO
					cout << "###############true#################" << endl;
#endif
					return true;
				}
				else 
				{
					m = i;
					if (SrcStr[m] == SrcStr[j])
					{//m值更新，重新比较
						m++;
					}
				}
			}
			//cout << "m:"<<m  << "j:" <<j<< endl;
		}
	}
#if DEBUG_INFO
	cout << "###############false##################" << endl;
#endif
	return false;
}
int main()
{
	string Inputstr;
	vector<string> OutResult;

	while (getline(cin, Inputstr))
	{
		if (Inputstr.size() <= 8)
		{//第一个要求，长度大于8
			OutResult.push_back(PASSWD_NG);
#if DEBUG_INFO
			cout << "Passwd size >8:" << Inputstr << endl;
#endif
			continue;
		}
		int PasswdClass[4] = { 0 };
		int PasswdClassCnt = 0;
		int i = 0;
		for (auto it= Inputstr.begin();it!= Inputstr.end();it++)
		{
			if ((*it <= 'Z') && (*it >= 'A')) PasswdClass[0] = 1;
			else if ((*it <= 'z') && (*it >= 'a')) PasswdClass[1] = 1;
			else if ((*it <= '9') && (*it >= '0')) PasswdClass[2] = 1;
			else PasswdClass[3] = 1;
		}
		for (i = 0; i < 4; i++)
		{
			PasswdClassCnt += PasswdClass[i];
		}
		if (PasswdClassCnt < 3)
		{//第二个要求，种类大于3
#if DEBUG_INFO
			cout << "Passwd class < 3: " << Inputstr << endl;
#endif
			OutResult.push_back(PASSWD_NG);
			continue;
		}
		if (FindRepeatStr(Inputstr,2))
		{
			OutResult.push_back(PASSWD_NG);
			continue;
		}
		OutResult.push_back(PASSWD_OK);
#if DEBUG_INFO
		cout << "passwd ok: "<< Inputstr << endl;
#endif
	}
	for (auto it = OutResult.begin(); it != OutResult.end(); it++)
	{
		cout << *it << endl;
	}
	while (getchar() != 'c')
	{
	}
	return 0;
}