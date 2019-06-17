/*题目描述
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const vector<string> Numstr = {"zero","one","two","three","four","five","six","seven","eight","nine"};
string PasswordNum;
int Decode(string &InputPassword,string &OutPasswd)
{
	return 0;
}
int FindNum(string Inputword)
{
	int i = 0,j=0;
	int found=0;
	int count = 0;
	for (i = 0; i < Inputword.size();)
	{
		for (j = 0; j < Numstr.size(); j++)
		{
			found = Inputword.find(Numstr[j],i);
			if (found==string::npos)
			{//未找到，进入下一轮循环
				continue;
			}
			if (found == i)
			{
				PasswordNum.append(to_string(j));
				//找到，更换寻找位置，结束循环
				i = found + Numstr[j].size();
				break;
			}
		}
	}
	return -1;
}
//输入：onethreefoursixninenine
//输出：134699
int main()
{
	int i = 0;
	string Inputstr;
	while (getline(cin, Inputstr))
	{
		//1.将输入字符串大写全改成小写
		for (i = 0; i < Inputstr.size(); i++)
		{
			if (Inputstr[i] <= 'Z' && (Inputstr[i] >= 'A'))
			{
				Inputstr[i] += 32;
			}
		}
		FindNum(Inputstr);
		cout << PasswordNum << endl;
		Inputstr.clear();
		PasswordNum.clear();
	}
	while (getchar() != 'c')
	{
	}
	return 0;
}