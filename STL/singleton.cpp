#include<iostream>
#include<atomic>
#include<mutex>
#include<thread>
#include <windows.h>
using namespace std;

// �����࣬�������ʵ���Ĵ���
class Data { 
public:
	Data() { cout << "Data() Ĭ�Ϲ���" << endl; }
	Data(const Data& src) { cout << "Data() ��������" << endl; }
	~Data() { cout << "Data() Ĭ������" << endl; }
};


/*
	��򵥵�ʵ�֣�����C++11��̬�ֲ�������ʼ�����̰߳�ȫ��
*/

// ����ʽ
//class Singleton{
//private:
//	Singleton() {
//		data = new Data();
//	}
//	~Singleton() {
//		delete data;
//		data = nullptr;
//	}
//	Singleton(const Singleton&)= delete;// ˽�л���������
//	Singleton& operator=(const Singleton&)= delete;// ˽�л���ֵ�����
//	Data* data;
//public:
//	static Singleton& getInstance() { // ������ʱ�ų�ʼ�����������Ǿֲ���̬�������������ʱ������һ�οռ�
//		static Singleton instance; // C++11�涨��local static�ڶ��߳������µĳ�ʼ����Ϊ��Ҫ���������֤���ڲ���̬�������̰߳�ȫ�ԡ�
//		return instance;
//	}
//};
//
// //����ʽ
//class Singleton {
//private:
//	Singleton() { data = new Data();}
//	~Singleton() {		
//		delete data;
//		data = nullptr;
//	}
//	Singleton(const Singleton&)= delete;
//	Singleton& operator=(const Singleton&) = delete;
//	Data* data;
//	static Singleton instance;
//	
//public:
//	
//	static Singleton& getInstance() {
//		return instance;
//	}
//};
//Singleton Singleton::instance; // ���岢��ʼ����̬��Ա


/*
	����ʽʹ��˫�ؼ��������Ʊ�֤�̰߳�ȫ��ʹ��atomic��֤�����������ԭ���ԣ�ʹ��Ƕ���ฺ���ͷŵ�������
*/
class Singleton{
private:
	Singleton() {
		data = new Data();
	}
	~Singleton() {
		delete data;
		data = nullptr;
	}
	Singleton(const Singleton&) = delete;// ˽�л��������죬����ʽ��ֹ����
	Singleton& operator=(const Singleton&) = delete;// ˽�л���ֵ�����������ʽ��ֹ����

	class Release {
	public: // ע�⣺���publicһ��Ҫ��!!!
		~Release() {
			if (Singleton::instance != nullptr) {
				delete instance;
				instance = nullptr;
				cout << "Ƕ��������, ��Դ�ͷ�" << endl;
			}
		};
	};
private:
	static Release release; // �ͷ���Դ��Ƕ���࣬�ó������ʱ�ܹ��Զ��ͷ���Դ��ҲҪ����Ϊ��̬��Ա���������ں͵���һ�£���
	Data* data; // ����
	static atomic<Singleton*> instance; // ����Ϊԭ�ӱ���
	static mutex m_utex; // ȫ����
public:
	static Singleton* getInstance() { // ������ʱ�ų�ʼ�����������Ǿֲ���̬�������������ʱ������һ�οռ�
		Singleton* tmp = instance.load();
		if (tmp == nullptr) {
			lock_guard<mutex>lock(m_utex);
			tmp = instance.load();
			cout << "����" << endl;
			if (tmp == nullptr) {
				cout << "��ʼ��" << endl;
				tmp = new Singleton();
				instance.store(tmp);
			}
		}
		return tmp;
	}
};
atomic<Singleton*> Singleton::instance; //���ⶨ�徲̬��Ա(���ﲢ�ǳ�ʼ��������������Ȼ������ģʽ)
mutex Singleton::m_utex;
Singleton::Release Singleton::release;

void myThread() {
	Singleton::getInstance();
	cout << "����ʵ��" << endl;
}

//int main() {
//	// �ú����֤������������main()����֮ǰ����֮��
//	// ����Ƕ���ʽ������main����֮ǰ������ʽ���ڵ�һ������֮��
//	cout << "========" << endl;
//	thread t1(&myThread);
//	//Sleep(1000); // ��1s֮��Ͳ����ټ��������ӵĻ������߳��л����ظ���������ֻ����һ�ι��캯��
//	thread t2(&myThread);
//	thread t3(&myThread);
//	thread t4(&myThread);
//	thread t5(&myThread);
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//	t5.join();
//	return 0;
//}

