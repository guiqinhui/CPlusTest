#include "stdio.h"  
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <functional>
#include <list>
#include <mutex>

using namespace std;
#if 1
//单例设计模式
std::mutex resource_mutex;
class s_cls
{
public:
	static s_cls * GetInstance()//静态成员函数
	{
		if (pInstance == NULL)//提高效率
		{
			std::lock_guard<std::mutex> mylock(resource_mutex);
			if (pInstance == NULL)
			{
				pInstance = new s_cls();
				static CRecycle cr;
			}
		}
		return pInstance;
	}
	class CRecycle//使用类回收资源
	{
	public:
		~CRecycle()
		{
			if (s_cls::pInstance != NULL)
			{
				delete s_cls::pInstance;
				s_cls::pInstance = NULL;
			}
		}
	};
	void Func(void)
	{
		cout << "this is a test!" << endl;
	}
	
private:
	s_cls(){}//私有化构造函数
	static s_cls *pInstance;
};
s_cls *s_cls::pInstance = NULL;
void mythread(void)
{
	cout << "我的线程开始执行,threadid: "<<this_thread::get_id() << endl;
	s_cls *pca = s_cls::GetInstance();
	cout << "我的线程结束执行!" << endl;
	return;
}
int main(int *agrc, char *argv[])
{
	std::thread mythread1(mythread);
	std::thread mythread2(mythread);
	return 0;
}
#endif
#if 0
//互斥信号实例
class MYMSG
{
public:
	void myOutMsg()
	{
		int Val = 0;
		while (1)
		{
			if (!msgRecvQ.empty())
			{
				
				{
					//std::lock_guard<std::mutex> mymutexguard(msg_mutex);
					
					msg_mutex.lock();
					std::unique_lock<std::mutex> mymutexguard(msg_mutex, std::adopt_lock);
					Val = msgRecvQ.front();//从队列头取数据
					msgRecvQ.pop_front();//取完将数据从队列中移除
					////std::unique_lock<std::mutex> mymutexguard(msg_mutex,std::try_to_lock);
					//if (mymutexguard.owns_lock())
					//{//拿到锁，执行操作
					//	Val = msgRecvQ.front();//从队列头取数据
					//	msgRecvQ.pop_front();//取完将数据从队列中移除
					//}
					//else
					//{//未拿到锁
					//	continue;
					//}
					//msg_mutex.unlock();
				}
				cout << "msg is:" << Val << endl;
			}
			else
			{
				cout << "Message is empty!" << endl;
			}
		}
	}
	void myInMsg(void)
	{
		for (int i = 0; i < 10000; i++)
		{
			cout << "insert msg is:" << i << endl;
			{
				//std::lock_guard<std::mutex> mymutexguard(msg_mutex);
				std::unique_lock<std::mutex> mymutexguard(msg_mutex);
				//msg_mutex.lock();
				msgRecvQ.push_back(i);//往队列中写数据
				//msg_mutex.unlock();
			}
		}
	}
private:
	std::list<int> msgRecvQ;//消息队列
	std::mutex msg_mutex;
};
int main(int *argc, char *argv[])
{
	MYMSG mymsg;
	std::thread mypushmsg(&MYMSG::myInMsg, &mymsg);
	std::thread mypopmsg(&MYMSG::myOutMsg, &mymsg);
	mypushmsg.join();
	mypopmsg.join();
	return 0;
}
#endif
#if 0
class MT
{
public:
	int tval;
	MT(int a):tval(a)
	{
		cout << "MT的构造函数执行地址" << this <<" Thread_id:"<<std::this_thread::get_id()<< endl;
	}
	MT(const MT &a)
	{
		cout << "MT的拷贝构造函数执行地址" << this << " Thread_id:" << std::this_thread::get_id() << endl;
	}
	~MT()
	{
		cout << "MT的析构函数执行地址" << this << " Thread_id:" << std::this_thread::get_id() << endl;
	}
	
};
void MyThread(const MT &pmybuf)//使用了引用及指针
{
	cout <<"buf的地址："<< &pmybuf << " Thread_id:" << std::this_thread::get_id() << endl;
}
void MyThread2(int &i)
{
	i = 12;
	cout << "i的值：" << i << " Thread_id:" << std::this_thread::get_id() << endl;
}
int main(int *argc, char *argv[])
{
	int var=1;
	cout << "主线程id："<< std::this_thread::get_id() << endl;
	cout << "var修改前的值：" << var << endl;
	thread mythread(MyThread2, std::ref(var));
	cout << "var修改后的值："<< var << endl;
#if 1
	mythread.join();	
#else
	mythread.detach();
#endif
	cout << "这是一个主线程!" << endl;
	return 0;
}
//int main(int *argc, char *argv[])
//{
//	int var=1;
//	cout << "主线程id："<< std::this_thread::get_id() << endl;
//	thread mythread(MyThread, MT(var));
//#if 0
//	mythread.join();	
//#else
//	mythread.detach();
//#endif
//	cout << "这是一个主线程!" << endl;
//	return 0;
//}
#if 0
void myprint(int idnum)
{
	cout << "子线程开始执行：" << idnum << endl;
}
int main(int *argc, char *argv[])
{
	//1、创建多个线程
	vector<thread> mythreads;
	for (int i = 0; i < 10; i++)
	{
		mythreads.push_back(thread(myprint,i));
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)
	{
		iter->join();//分别等待线程结束后返回
	}
	cout << "this is main thread end！" << endl;
}
#endif
#endif
