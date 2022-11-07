#include<iostream>
using namespace std;
// ��̳��У�ÿһ���Ĺ��캯����Ҫд�������ĳ�ʼ�����������û�������ָ���ľ���������;���˭���������Ĺ���
namespace ns20221107{
	class A {
	public:
		A() {
			cout << "A���캯��" << endl;
		}
		~A() {
			cout << "A��������" << endl;
		}
	};

	class B : virtual public A {
	public:
		B():A() {
			cout << "B���캯��" << endl;
		}
		~B() {
			cout << "B��������" << endl;
		}
	};

	class C : virtual public A {
	public:
		C() :A() {
			cout << "C���캯��" << endl;
		}
		~C() {
			cout << "C��������" << endl;
		}
	};

	class D : public B, public C {
	public:
		D() :A() {
			cout << "D���캯��" << endl;
		}
		~D() {
			cout << "D��������" << endl;
		}
	};
}

//int main() {
//	ns20221107::B d;
//	return 0;
//}