#include<iostream>
#include<atomic>
#include<mutex>
#include<thread>
#include <windows.h>
using namespace std;

// 数据类，用来检测实例的创建
class Data { 
public:
	Data() { cout << "Data() 默认构造" << endl; }
	Data(const Data& src) { cout << "Data() 拷贝构造" << endl; }
	~Data() { cout << "Data() 默认析构" << endl; }
};


/*
	最简单的实现，利用C++11静态局部变量初始化的线程安全性
*/

// 懒汉式
//class Singleton{
//private:
//	Singleton() {
//		data = new Data();
//	}
//	~Singleton() {
//		delete data;
//		data = nullptr;
//	}
//	Singleton(const Singleton&)= delete;// 私有化拷贝构造
//	Singleton& operator=(const Singleton&)= delete;// 私有化赋值运算符
//	Data* data;
//public:
//	static Singleton& getInstance() { // 被引用时才初始化，且由于是局部静态变量，多次引用时仅分配一次空间
//		static Singleton instance; // C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
//		return instance;
//	}
//};
//
// //饿汉式
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
//Singleton Singleton::instance; // 定义并初始化静态成员


/*
	懒汉式使用双重检查加锁机制保证线程安全，使用atomic保证对象构造操作的原子性，使用嵌套类负责释放单例对象
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
	Singleton(const Singleton&) = delete;// 私有化拷贝构造，并显式禁止调用
	Singleton& operator=(const Singleton&) = delete;// 私有化赋值运算符，并显式禁止调用

	class Release {
	public: // 注意：这个public一定要加!!!
		~Release() {
			if (Singleton::instance != nullptr) {
				delete instance;
				instance = nullptr;
				cout << "嵌套类析构, 资源释放" << endl;
			}
		};
	};
private:
	static Release release; // 释放资源的嵌套类，让程序结束时能够自动释放资源，也要设置为静态成员，生命周期和单例一致！！
	Data* data; // 数据
	static atomic<Singleton*> instance; // 声明为原子变量
	static mutex m_utex; // 全局锁
public:
	static Singleton* getInstance() { // 被引用时才初始化，且由于是局部静态变量，多次引用时仅分配一次空间
		Singleton* tmp = instance.load();
		if (tmp == nullptr) {
			lock_guard<mutex>lock(m_utex);
			tmp = instance.load();
			cout << "加锁" << endl;
			if (tmp == nullptr) {
				cout << "初始化" << endl;
				tmp = new Singleton();
				instance.store(tmp);
			}
		}
		return tmp;
	}
};
atomic<Singleton*> Singleton::instance; //类外定义静态成员(这里并非初始化！！！所以依然是懒汉模式)
mutex Singleton::m_utex;
Singleton::Release Singleton::release;

void myThread() {
	Singleton::getInstance();
	cout << "调用实例" << endl;
}

//int main() {
//	// 用横杠验证单例构造是在main()函数之前还是之后
//	// 如果是饿汗式，会在main函数之前，懒汉式则在第一次引用之后
//	cout << "========" << endl;
//	thread t1(&myThread);
//	//Sleep(1000); // 加1s之后就不会再加锁，不加的话由于线程切换会重复加锁，但只调用一次构造函数
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

