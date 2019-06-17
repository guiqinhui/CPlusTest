/*
第9节：
一、async、future
std::async std::future创建后台任务并返回值
希望线程返回一个结果
async：是一个函数模板，用于启动一个异步任务，启动起来一个异步任务后，返回一个future对象,这个future对象里就含有线程入口函数所返回的结果，我们可以通过future对象的成员函数get()获取韩函数的返回值
future：将来的意思，有人也称呼future提供了一种访问异步操作结果的机制，就是说这个结果你可能没有办法马上获得
在线程执行完毕的时候，你就能够拿到结果了。
可以这么理解：这个future里会保持一个值，在将来的某个时间取得
二、packaged_task
packaged_task:打包任务，把任务包装起来
是个类模板
*/
#include "stdio.h"
#include <iostream>
#include <thread>
#include <future>
using namespace std;
#if 0
//一、async、future
#if 1
class A
{
public:
	int mythread(int argv)
	{
		cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
		cout << "mythread param1:" << argv << endl;
		//休息一段时间
		std::chrono::milliseconds dura(5000);//5s时间
		std::this_thread::sleep_for(dura);//休息一段时长
		cout << "mythread end,id:" << std::this_thread::get_id() << endl;
		return 5;
	}
};
#else
int mythread()
{ 
	cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
	//休息一段时间
	std::chrono::milliseconds dura(5000);//5s时间
	std::this_thread::sleep_for(dura);//休息一段时长
	cout << "mythread end,id:" << std::this_thread::get_id() << endl;
	return 5;
}
#endif
int main(int *argc, char *argv[])
{
	int var = 100;
	A a;
	cout << "主线程 id：" << std::this_thread::get_id() << endl;
	//第一个参数是类中的成员函数为线程的入口函数
	//第二个参数是创建的类对象
	//第三个参数是线程入口函数的参数
	std::future<int> result = std::async(&A::mythread,&a, var);//创建一个线程并开始执行，绑定关系，流程并不卡到这里
	cout << "继续..." << endl;
	cout << result.get() << endl;//卡在这里等待mythread()执行完毕，拿到结果
	cout << "主线程结束！" << endl;
	return 0;
}
#else
int mythread(int argv)
{
	cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
	cout << "mythread param1:" << argv << endl;
	//休息一段时间
	std::chrono::milliseconds dura(5000);//5s时间
	std::this_thread::sleep_for(dura);//休息一段时长
	cout << "mythread end,id:" << std::this_thread::get_id() << endl;
	return 5;
}
int main(int *argc, char *argv[])
{
	int var = 100;
	cout << "主线程 id：" << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread);//把线程入口函数包装起来
	std::thread th(std::ref(mypt), var);//以包装的函数作为线程入口函数
	th.join();//等待子线程返回
	std::future<int> result= mypt.get_future();//获取函数包装器的返回值
	cout << result.get() << endl;
	cout << "主线程结束！" << endl;
	return 0;
}
#endif