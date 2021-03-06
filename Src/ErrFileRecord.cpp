/*题目描述
开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。
处理：
1、 记录最多8条错误记录，循环记录，对相同的错误记录（净文件名称和行号完全匹配）只记录一条，错误计数增加；
2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；
3、 输入的文件可能带路径，记录文件名称不能带路径。
输入描述 :
一行或多行字符串。每行包括带路径文件名称，行号，以空格隔开。
输出描述 :
将所有的记录统计并将结果输出，格式：文件名 代码行数 数目，一个空格隔开，如：
示例1
输入
E : \V1R2\product\fpgadrive.c   1325
输出
		fpgadrive.c 1325 1*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define DEBUG_INFO	1
using namespace std;

struct ErrFileInfo
{
	string FileName;
	string CodeLine;
	int TotalNum=1;
	bool operator==(const ErrFileInfo &a)
	{//重载操作符==
		if ((a.FileName == FileName)
			&& (a.CodeLine == CodeLine))
		{
			return true;
		}
		return false;
	}
};
int main()
{
	string Inputstr;
	vector<ErrFileInfo> RecordFile;
	vector<ErrFileInfo>::iterator it;

	while (getline(cin, Inputstr))
	{
		size_t f1 = Inputstr.find_last_of('\\');
		size_t f2 = Inputstr.find_first_of(' ');
		string Inputfilename = Inputstr.substr(f1+1, f2-f1-1);
		ErrFileInfo tmprecord;
		f2 = Inputstr.find_last_of(' ');
		string InputLineNum = Inputstr.substr(f2+1, Inputstr.size()-f2);
		if (Inputfilename.size() > 16)
		{//文件名长度超过16，则取最后16个字符
			Inputfilename = Inputfilename.substr(Inputfilename.size()-16,16);
		}
		tmprecord.FileName = Inputfilename;
		tmprecord.CodeLine = InputLineNum;
		it = find(RecordFile.begin(), RecordFile.end(), tmprecord);//需要重载操作符==
		if (it == RecordFile.end())
		{//没有重复记录，存入容器中
			RecordFile.push_back(tmprecord);
		}
		else
		{//有重复记录，自加
			it->TotalNum++;
		}
	}
	int i = 0, start_cnt = 0;
	if (RecordFile.size() > 8)
	{
		start_cnt = RecordFile.size() - 8;
	}
	for (i = start_cnt; i < RecordFile.size(); i++)
	{
		cout << RecordFile[i].FileName << ' ' << RecordFile[i].CodeLine << ' ' << RecordFile[i].TotalNum << endl;
	}
}