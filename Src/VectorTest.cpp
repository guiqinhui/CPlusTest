
// vector::push_back
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
int main()
{
	std::vector<string> myvector;
	string myint;
	int Count=0;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	while (cin >> myint)
	{
		myvector.push_back(myint);
		Count++;
		cout << "Input Count is: " << Count << endl;
		cout << "Input string is:" << myint << endl;
	}

	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
	while (1)
	{
		if (getchar() == 'c')
		{
			break;
		}
	}
	
	return 0;
}
*/
//将一个英文语句以单词为单位逆序排放。例如“I am a boy”，逆序排放后为“boy a am I”
//所有单词之间用一个空格隔开，语句中除了英文字母外，不再包含其他字符
int main()
{
	string Inputstr;
	vector<string> InputVector;
	//while (getline(cin, Inputstr))
	{
		while (cin >> Inputstr)
		{
			InputVector.push_back(Inputstr);
		}
		for (int i = InputVector.size()-1; i>=0; i--)
		{
			cout << InputVector[i] << ' ';
		}
		while (1)
		{
			if (getchar() == 'c')
			{
				break;
			}
		}
	}
	return 0;
}