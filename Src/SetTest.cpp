#include <iostream>
#include <string>
#include <set>
using namespace std;
int main()
{
	string Inputstr;
	char InputChar;

	while (getline(cin, Inputstr))
	{
		set<char> InputSet;
		for (int i = 0; i<Inputstr.length(); i++)
		{
			InputChar = (char)Inputstr[i];
			if ((InputChar >= 0) && (InputChar <= 127))
			{
				cout << "insert: "<< InputChar << endl;
				InputSet.insert(InputChar);
			}
		}
		for (set<char>::iterator it = InputSet.begin(); it != InputSet.end(); it++)
		{
			cout << "Inputset val: "<<*it << endl;
		}
		cout << InputSet.size() << endl;
	}
}