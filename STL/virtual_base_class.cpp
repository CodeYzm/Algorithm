#include<iostream>
using namespace std;
// 虚继承中，每一级的构造函数都要写有虚基类的初始化，最终由用户区代码指定的具体对象类型决定谁负责虚基类的构造
namespace ns20221107{
	class A {
	public:
		A() {
			cout << "A构造函数" << endl;
		}
		~A() {
			cout << "A析构函数" << endl;
		}
	};

	class B : virtual public A {
	public:
		B():A() {
			cout << "B构造函数" << endl;
		}
		~B() {
			cout << "B析构函数" << endl;
		}
	};

	class C : virtual public A {
	public:
		C() :A() {
			cout << "C构造函数" << endl;
		}
		~C() {
			cout << "C析构函数" << endl;
		}
	};

	class D : public B, public C {
	public:
		D() :A() {
			cout << "D构造函数" << endl;
		}
		~D() {
			cout << "D析构函数" << endl;
		}
	};
}

//int main() {
//	ns20221107::B d;
//	return 0;
//}