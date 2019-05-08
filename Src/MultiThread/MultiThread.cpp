#include   "stdio.h"  
#include<iostream>
#include <thread>
using namespace std;

void MyThread(void)
{
	cout << "This is my thread!" << endl;
	cout << "My thread is end!" << endl;

}
class MT
{
public:
	void operator()()//一定要重载()操作符，不能带参数
	{
		cout << "This is my thread!" << endl;
		cout << "My thread is end!" << endl;
	}
};
int main(int *argc, char *argv[])
{
	auto mylamdbathread = [] {
		cout << "This is my lamdba thread!" << endl;
		cout << "My lamdba thread is end!" << endl;
	};
	thread mythread(mylamdbathread);//创建了线程，线程执行起点（入口）为mt，并开始执行
	mythread.join();//主、子线程汇合，主线程阻塞到这里等待Mythread()执行完，当子线程执行完毕，这个join()执行完毕，主线程就继续往下走
	//mythread.detach();//主、子线程分离，主线程可以自由结束，不用管子线程，主线程与子线程失去联系，子线程由运行时库负责清理该线程相关资源
				
	cout << "这是一个主线程!" << endl;
	return 0;
}