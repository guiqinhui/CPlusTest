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
//�������ģʽ
std::mutex resource_mutex;
class s_cls
{
public:
	static s_cls * GetInstance()//��̬��Ա����
	{
		if (pInstance == NULL)//���Ч��
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
	class CRecycle//ʹ���������Դ
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
	s_cls(){}//˽�л����캯��
	static s_cls *pInstance;
};
s_cls *s_cls::pInstance = NULL;
void mythread(void)
{
	cout << "�ҵ��߳̿�ʼִ��,threadid: "<<this_thread::get_id() << endl;
	s_cls *pca = s_cls::GetInstance();
	cout << "�ҵ��߳̽���ִ��!" << endl;
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
//�����ź�ʵ��
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
					Val = msgRecvQ.front();//�Ӷ���ͷȡ����
					msgRecvQ.pop_front();//ȡ�꽫���ݴӶ������Ƴ�
					////std::unique_lock<std::mutex> mymutexguard(msg_mutex,std::try_to_lock);
					//if (mymutexguard.owns_lock())
					//{//�õ�����ִ�в���
					//	Val = msgRecvQ.front();//�Ӷ���ͷȡ����
					//	msgRecvQ.pop_front();//ȡ�꽫���ݴӶ������Ƴ�
					//}
					//else
					//{//δ�õ���
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
				msgRecvQ.push_back(i);//��������д����
				//msg_mutex.unlock();
			}
		}
	}
private:
	std::list<int> msgRecvQ;//��Ϣ����
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
		cout << "MT�Ĺ��캯��ִ�е�ַ" << this <<" Thread_id:"<<std::this_thread::get_id()<< endl;
	}
	MT(const MT &a)
	{
		cout << "MT�Ŀ������캯��ִ�е�ַ" << this << " Thread_id:" << std::this_thread::get_id() << endl;
	}
	~MT()
	{
		cout << "MT����������ִ�е�ַ" << this << " Thread_id:" << std::this_thread::get_id() << endl;
	}
	
};
void MyThread(const MT &pmybuf)//ʹ�������ü�ָ��
{
	cout <<"buf�ĵ�ַ��"<< &pmybuf << " Thread_id:" << std::this_thread::get_id() << endl;
}
void MyThread2(int &i)
{
	i = 12;
	cout << "i��ֵ��" << i << " Thread_id:" << std::this_thread::get_id() << endl;
}
int main(int *argc, char *argv[])
{
	int var=1;
	cout << "���߳�id��"<< std::this_thread::get_id() << endl;
	cout << "var�޸�ǰ��ֵ��" << var << endl;
	thread mythread(MyThread2, std::ref(var));
	cout << "var�޸ĺ��ֵ��"<< var << endl;
#if 1
	mythread.join();	
#else
	mythread.detach();
#endif
	cout << "����һ�����߳�!" << endl;
	return 0;
}
//int main(int *argc, char *argv[])
//{
//	int var=1;
//	cout << "���߳�id��"<< std::this_thread::get_id() << endl;
//	thread mythread(MyThread, MT(var));
//#if 0
//	mythread.join();	
//#else
//	mythread.detach();
//#endif
//	cout << "����һ�����߳�!" << endl;
//	return 0;
//}
#if 0
void myprint(int idnum)
{
	cout << "���߳̿�ʼִ�У�" << idnum << endl;
}
int main(int *argc, char *argv[])
{
	//1����������߳�
	vector<thread> mythreads;
	for (int i = 0; i < 10; i++)
	{
		mythreads.push_back(thread(myprint,i));
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)
	{
		iter->join();//�ֱ�ȴ��߳̽����󷵻�
	}
	cout << "this is main thread end��" << endl;
}
#endif
#endif
