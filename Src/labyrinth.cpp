/*题目描述

定义一个二维数组N*M（其中2<=N<=10;2<=M<=10），如5 × 5数组下所示：
int maze[5][5] = {
0, 1, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
};
它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。入口点为[0,0],既第一空格是可以走的路。
Input
一个N × M的二维数组，表示一个迷宫。数据保证有唯一解,不考虑有多解的情况，即迷宫只有一条通道。
Output
左上角到右下角的最短路径，格式如样例所示。
Sample Input
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
Sample Output
(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)

输入描述:
输入两个整数，分别表示二位数组的行数，列数。再输入相应的数组，其中的1表示墙壁，0表示可以走的路。数据保证有唯一解,不考虑有多解的情况，即迷宫只有一条通道。

输出描述:
左上角到右下角的最短路径，格式如样例所示。

示例1
输入
5 5
0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
输出
(0,0)
(1,0)
(2,0)
(2,1)
(2,2)
(2,3)
(2,4)
(3,4)
(4,4)*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//递归向4个方向查找
vector<vector<int>> Labyrinth;
vector<vector<int>> PathFind;
vector<vector<int>> PathBest;
int MX = 0, MY=0;
/*
设计思路：递归查找
1.将当期节点加入路径，并设置为已走
2.判断是否为出口，是则输出路径，保存结果，否则跳转到第4步
3.分别从4个方向（上下左右）判断是否可走，如果可走，则递归走改点
4.不可走则退出，并恢复已走，设置为未走，并将当期节点移除路径
*/
void findExitPath(int x, int y)
{
	//1.将当期节点加入路径，并设置为已走
	Labyrinth[x][y] = 1;
	PathFind.push_back({x,y});
	//判断是否为出口，是则输出路径，保存结果
	if (x == (MX - 1) && (y == (MY - 1)))
	{//已寻找到出口
		if (PathBest.empty()||(PathBest.size()>PathFind.size()))
		{//寻找最短路径
			PathBest = PathFind;
		}
		
	}
	//3.分别从4个方向（上下左右）判断是否可走，如果可走，则递归走改点
	if (((y - 1) >= 0) && (Labyrinth[x][y - 1] == 0))
	{//上
		findExitPath(x, y - 1);
	}
	if(((y + 1) < MY) && (Labyrinth[x][y + 1] == 0))
	{//下
		findExitPath(x, y + 1);
	}
	if (((x - 1) >=0) && (Labyrinth[x - 1][y] == 0))
	{//左
		findExitPath(x - 1, y);
	}
	if (((x + 1) < MX) && (Labyrinth[x+1][y] == 0))
	{//右
		findExitPath(x+1, y);
	}
	//4.恢复现场
	Labyrinth[x][y] = 0;
	PathFind.pop_back();
}

int main()
{

	while (cin>>MX>>MY)
	{
		Labyrinth = vector<vector<int>>(MX,vector<int>(MY,0));//初始化所有值为0
		for (auto &i : Labyrinth)//c++11 for循环新特性
		{
			for (auto &j : i)
			{
				cin >> j;//给二维数组赋值
			}
		}
		PathFind.clear();
		PathBest.clear();
		findExitPath(0,0);//从(0,0)位置开始查找
		for (auto n : PathBest)
		{
			cout << '(' <<n[0]<<','<< n[1] << ')'<< endl;
		}
	}
	
	while (getchar() != 'c')
	{
	}
	return 0;
}