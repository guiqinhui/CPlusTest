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
	void operator()()//һ��Ҫ����()�����������ܴ�����
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
	thread mythread(mylamdbathread);//�������̣߳��߳�ִ����㣨��ڣ�Ϊmt������ʼִ��
	mythread.join();//�������̻߳�ϣ����߳�����������ȴ�Mythread()ִ���꣬�����߳�ִ����ϣ����join()ִ����ϣ����߳̾ͼ���������
	//mythread.detach();//�������̷߳��룬���߳̿������ɽ��������ù����̣߳����߳������߳�ʧȥ��ϵ�����߳�������ʱ�⸺��������߳������Դ
				
	cout << "����һ�����߳�!" << endl;
	return 0;
}