// CPlusTest.cpp: 定义控制台应用程序的入口点。
//

#include   "stdio.h"  
#include<iostream>
using namespace std;
class FatherClass
{
public:
	FatherClass()
	{
		printf("FatherClass Create!\n");
	}
 ~FatherClass()
	{
		printf("Delete   class   FatherClass\n");
	}
};
class SubClass:public FatherClass
{
public:
	SubClass()
	{
		printf("SubClass Create!\n");
	}
	~SubClass()
	{
		printf("Delete   class   SubClass\n");
	}
};
void LambdaTest(void)
{
	int x = 10;

	auto add_x = [x](int a) { return a + x; };  // 复制捕捉x
	auto multiply_x = [&x](int a) { return a * x; };  // 引用捕捉x

	cout << add_x(5) << " " << multiply_x(5) << endl;
	// 输出：20 100
	return;
}
int main(int   argc, char*   argv[])
{
	FatherClass   *b = new SubClass;
	delete   b;
	LambdaTest();
	getchar();
	return   0;
}
