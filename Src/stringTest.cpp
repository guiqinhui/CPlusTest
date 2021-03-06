#include <iostream>
#include <string>
using namespace std;
/*
int main()
{
	int Input;
	int tmp;
	int i = 0;
	string Output;
	while (cin >> Input)
	{
		while (Input)
		{
			tmp = Input % 10;
			Input = Input / 10;
			cout << tmp+'0' << endl;
		}
		cout << Output << endl;
	}
	return 0;
}*/

//开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。
void ParseAsix(string PoseStr, int *Xpos, int *Ypos)
{
	int xflag = 0, yflag = 0;
	int Poseval = 0;
	switch (PoseStr[0])
	{
	case 'W':
	{
		xflag = 0;
		yflag = 1;
	}break;
	case 'S':
	{
		xflag = 0;
		yflag = -1;
	}break;
	case 'A':
	{
		xflag = -1;
		yflag = 0;
	}break;
	case 'D':
	{
		xflag = 1;
		yflag = 0;
	}break;
	default:return;
	}
	cout << "xflag:" << xflag << "yflag:" << yflag << endl;
	switch (PoseStr.size())
	{
	case 2:
	{//数字只有1位数
		if ((PoseStr[1]) <= '9' && (PoseStr[1] >= '0'))
		{
			Poseval = PoseStr[1] - '0';
		}
	}break;
	case 3:
	{//数字有2位数
		if (((PoseStr[1]) <= '9' && (PoseStr[1] >= '0'))
			&& ((PoseStr[2]) <= '9' && (PoseStr[2] >= '0')))
		{
			Poseval = PoseStr[1] - '0';
			Poseval = Poseval * 10 + PoseStr[2] - '0';
		}
	}break;
	default:break;
	}
	
	*Xpos = Poseval * xflag;
	*Ypos = Poseval * yflag;
	cout << "Xpos:" << *Xpos<<" Ypos:"<< *Ypos << endl;
}
int main()
{
	string inputstr;
	while (cin >> inputstr)
	{
		int x = 0, y = 0;
		int strpos = 0, posstart = 0;
		string findposstr;
		//寻找；
		while (1)
		{
			int xmove = 0, ymove = 0;
			strpos = inputstr.find(";",posstart,1);
			if (strpos == string::npos)
			{
				break;
			}
			cout << "strpos: " << posstart<<" "<< strpos << endl;
			findposstr = inputstr.substr(posstart, strpos- posstart);
			posstart = strpos + 1;
			cout << "findsubstr:"<< findposstr << endl;
			ParseAsix(findposstr, &xmove, &ymove);
			x += xmove;
			y += ymove;
			cout << x << ',' << y << endl;
			cout << "===============================" << endl;
		}
		cout << x << ',' << y << endl;
	}
	return 0;
}