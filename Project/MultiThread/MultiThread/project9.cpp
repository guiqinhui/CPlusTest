/*
��9�ڣ�
һ��async��future
std::async std::future������̨���񲢷���ֵ
ϣ���̷߳���һ�����
async����һ������ģ�壬��������һ���첽������������һ���첽����󣬷���һ��future����,���future������ͺ����߳���ں��������صĽ�������ǿ���ͨ��future����ĳ�Ա����get()��ȡ�������ķ���ֵ
future����������˼������Ҳ�ƺ�future�ṩ��һ�ַ����첽��������Ļ��ƣ�����˵�����������û�а취���ϻ��
���߳�ִ����ϵ�ʱ������ܹ��õ�����ˡ�
������ô��⣺���future��ᱣ��һ��ֵ���ڽ�����ĳ��ʱ��ȡ��
����packaged_task
packaged_task:������񣬰������װ����
�Ǹ���ģ��
*/
#include "stdio.h"
#include <iostream>
#include <thread>
#include <future>
using namespace std;
#if 0
//һ��async��future
#if 1
class A
{
public:
	int mythread(int argv)
	{
		cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
		cout << "mythread param1:" << argv << endl;
		//��Ϣһ��ʱ��
		std::chrono::milliseconds dura(5000);//5sʱ��
		std::this_thread::sleep_for(dura);//��Ϣһ��ʱ��
		cout << "mythread end,id:" << std::this_thread::get_id() << endl;
		return 5;
	}
};
#else
int mythread()
{ 
	cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
	//��Ϣһ��ʱ��
	std::chrono::milliseconds dura(5000);//5sʱ��
	std::this_thread::sleep_for(dura);//��Ϣһ��ʱ��
	cout << "mythread end,id:" << std::this_thread::get_id() << endl;
	return 5;
}
#endif
int main(int *argc, char *argv[])
{
	int var = 100;
	A a;
	cout << "���߳� id��" << std::this_thread::get_id() << endl;
	//��һ�����������еĳ�Ա����Ϊ�̵߳���ں���
	//�ڶ��������Ǵ����������
	//�������������߳���ں����Ĳ���
	std::future<int> result = std::async(&A::mythread,&a, var);//����һ���̲߳���ʼִ�У��󶨹�ϵ�����̲�����������
	cout << "����..." << endl;
	cout << result.get() << endl;//��������ȴ�mythread()ִ����ϣ��õ����
	cout << "���߳̽�����" << endl;
	return 0;
}
#else
int mythread(int argv)
{
	cout << "mythread start ,id:" << std::this_thread::get_id() << endl;
	cout << "mythread param1:" << argv << endl;
	//��Ϣһ��ʱ��
	std::chrono::milliseconds dura(5000);//5sʱ��
	std::this_thread::sleep_for(dura);//��Ϣһ��ʱ��
	cout << "mythread end,id:" << std::this_thread::get_id() << endl;
	return 5;
}
int main(int *argc, char *argv[])
{
	int var = 100;
	cout << "���߳� id��" << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread);//���߳���ں�����װ����
	std::thread th(std::ref(mypt), var);//�԰�װ�ĺ�����Ϊ�߳���ں���
	th.join();//�ȴ����̷߳���
	std::future<int> result= mypt.get_future();//��ȡ������װ���ķ���ֵ
	cout << result.get() << endl;
	cout << "���߳̽�����" << endl;
	return 0;
}
#endif