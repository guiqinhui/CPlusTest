#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int Num=0, move_num=0, tmp_move=0;
	int Height;
	vector<int> HeightVector;
	while (cin >> Num)
	{
		while (Num--)
		{
			cin >> Height;
			HeightVector.push_back(Height);
		}
		move_num = HeightVector.size();
		for (int i = 0; i<HeightVector.size(); i++)
		{
			for (int j = 0; j<HeightVector.size(); j++)
			{
				if (((i<j) && (HeightVector[i] >= HeightVector[j]))
					|| ((i>j) && (HeightVector[i] <= HeightVector[j])))
				{
					tmp_move++;
				}
			}
			if (tmp_move < move_num)
			{
				move_num = tmp_move;
			}
		}
		cout << move_num << endl;
	}
}