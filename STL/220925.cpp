#include<iostream>
using namespace std;

namespace y0925 {
	class A {
	public:
		A() { cout << "A" << endl; }
		~A() { cout << "!A" << endl; }
	};

	class B {
	public:
		B() { cout << "B" << endl; }
		~B() { cout << "!B" << endl; }
	};

	class C :public B {
	public:
		C() { cout << "C" << endl; }
		~C() { cout << "!C" << endl; }
	};
	class D :public A, C {
	public:
		D() { cout << "D" << endl; }
		~D() { cout << "!D" << endl; }
	};
}

//int main() {
	//��̳й�������˳������
	//y0925::D d;

	// *p++ �� (*p)++������++�������*�������ȼ���ͬ��������һ����Ľ��˳�������ҵ������Բ�������++����
	//int s[2] = { 1,2 };
	// int* p = s;
	//(*p)++; //ָ�������֮��++��Ҳ����ָ�����ֵ++
	// *p++; // ָ��++������+֮ǰ��ָ�룬Ȼ�������
	//cout << *p++ << " " << s[0] << endl;

	// int a = 080; // �Ƿ���ֵ

	//int i = 5,j = 5;
	//int p;
	//p = (i++) + (i++) + (i++);
	//cout << i << endl;
	//p = (++j) + (++j) + (++j);
	//cout << p << endl;

	// ֻ��unsigned��signedһ������Żή�ͣ�������ʧ
	// cout << a << endl;
	//long long c = -5;
	//unsigned int a = 1.0;
	//cout << c + a << endl;

	//int* p[4]; // �����ĸ�int��ָ���ָ������

	// ��������û��ȫ���б��ʼ������ʹ��Ĭ�Ϲ���
	//int a[][4] = { 1,2 };
	//cout << a[0][0] << endl; // 1
	//cout << a[0][1] << endl; // 2
	//cout << a[0][2] << endl; // 0
	//cout << a[0][3] << endl; // 0

	// float == 0.0�ǿ��Ե�
	//float a = 0.0;
	//if (a == 0.0) cout << "a == 0.0" << endl;
	//if (0 == a) cout << "0 == a" << endl;
//	return 0;
//}