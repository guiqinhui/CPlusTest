// CPlusTest.cpp: 定义控制台应用程序的入口点。
//

#include   "stdio.h"  
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
int main(int   argc, char*   argv[])
{
	FatherClass   *b = new SubClass;
	delete   b;
	getchar();
	return   0;
}
