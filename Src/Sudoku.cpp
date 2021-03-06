/*题目描述
问题描述：数独（Sudoku）是一款大众喜爱的数字逻辑游戏。玩家需要根据9X9盘面上的已知数字，推算出所有剩余空格的数字，并且满足每一行、每一列、每一个粗线宫内的数字均含1-9，并且不重复。
输入：
包含已知数字的9X9盘面数组[空缺位以数字0表示]
输出：
完整的9X9盘面数组
输入描述:
包含已知数字的9X9盘面数组[空缺位以数字0表示]
输出描述:
完整的9X9盘面数组
示例1
输入
0 9 2 4 8 1 7 6 3
4 1 3 7 6 2 9 8 5
8 6 7 3 5 9 4 1 2
6 2 4 1 9 5 3 7 8
7 5 9 8 4 3 1 2 6
1 3 8 6 2 7 5 9 4
2 7 1 5 3 8 6 4 9
3 8 6 9 1 4 2 5 7
0 4 5 2 7 6 8 3 1
输出
5 9 2 4 8 1 7 6 3
4 1 3 7 6 2 9 8 5
8 6 7 3 5 9 4 1 2
6 2 4 1 9 5 3 7 8
7 5 9 8 4 3 1 2 6
1 3 8 6 2 7 5 9 4
2 7 1 5 3 8 6 4 9
3 8 6 9 1 4 2 5 7
9 4 5 2 7 6 8 3 1
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//递归向4个方向查找
vector<vector<int>> CheckerBoard;
vector<vector<int>> PathFind;
vector<vector<int>> PathBest;
#define MX		9
#define MY		9
#define MAX_NUM	80//MX*MY-1
/*
设计思路：递归查找
判断所填入的数据是否合法
1.行是否合法，1-9无重复
2.列是否合法，1-9无重复
3.包含该位置在内的所有小九宫格是否合法
*/
bool CheckIsVaild(int Pos,int key)
{
	int x,y,i,j;
	x = Pos/MX;
	y = Pos%MY;
	//所在行是否合法
	for (i = 0; i < MX; i++)
	{
		if (CheckerBoard[i][y] == key)
		{
			return false;
		}
	}
	//所在列是否合法
	for (i = 0; i < MX; i++)
	{
		if (CheckerBoard[x][i] == key)
		{
			return false;
		}
	}
	//判断所在小九宫格是否合法
	int base_x = x / 3 * 3;
	int base_y = y / 3 * 3;
	for (i = base_x; i < base_x + 3; i++)
	{
		for (j = base_y; j < base_y++; j++)
		{
			if (CheckerBoard[x][i] == key)
			{
				return false;
			}
		}
	}
	return true;
}
/*
填充数字(深搜)
1.判断是否最后一个数字
2.找到值为0需要填充的位置
3.依次填入(1-9),并检查是否合法，合法则递归继续寻找直到找到合法的为止
*/
bool InsertNum(int Pos)
{
	int x, y, i, j;
	
	if (Pos == MAX_NUM)
	{
		return true;
	}
	x = Pos / MX;
	y = Pos % MY;
	if (CheckerBoard[x][y] != 0)
	{
		InsertNum(Pos+1);//继续寻找下一个位置
		return false;
	}
	for (i = 1; i < MX; i++)
	{//1-mx试数字

		if (!CheckIsVaild(Pos, i))
		{
			continue;
		}
		CheckerBoard[x][y] = i;
		if (!InsertNum(Pos + 1))//继续寻找下一个位置
		{
			CheckerBoard[x][y] = 0;
		}
	}
	return false;
}

int main()
{
	CheckerBoard = vector<vector<int>>(MX,vector<int>(MY,0));//初始化所有值为0
	for (auto &i : CheckerBoard)//c++11 for循环新特性
	{
		for (auto &j : i)
		{
			cin >> j;//给二维数组赋值
		}
	}

	InsertNum(0);//从(0,0)位置开始查找
	for (int i = 0; i < MX; i++)
	{
		for (int j = 0; j < MY; j++)
		{
			cout << CheckerBoard[i][j] << ' ';
		}
		cout << endl;
	}
	
	while (getchar() != 'c')
	{
	}
	return 0;
}