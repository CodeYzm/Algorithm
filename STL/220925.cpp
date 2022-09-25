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
	//多继承构造析构顺序问题
	//y0925::D d;

	// *p++ 与 (*p)++的区别：++与解引用*符号优先级相同，但是这一级别的结合顺序是由右到左，所以不加括号++优先
	//int s[2] = { 1,2 };
	// int* p = s;
	//(*p)++; //指针解引用之后++，也就是指向的数值++
	// *p++; // 指针++，返回+之前的指针，然后解引用
	//cout << *p++ << " " << s[0] << endl;

	// int a = 080; // 非法数值

	//int i = 5,j = 5;
	//int p;
	//p = (i++) + (i++) + (i++);
	//cout << i << endl;
	//p = (++j) + (++j) + (++j);
	//cout << p << endl;

	// 只有unsigned与signed一起运算才会降低，精度损失
	// cout << a << endl;
	//long long c = -5;
	//unsigned int a = 1.0;
	//cout << c + a << endl;

	//int* p[4]; // 申请四个int型指针的指针数组

	// 申请数组没有全部列表初始化，会使用默认构造
	//int a[][4] = { 1,2 };
	//cout << a[0][0] << endl; // 1
	//cout << a[0][1] << endl; // 2
	//cout << a[0][2] << endl; // 0
	//cout << a[0][3] << endl; // 0

	// float == 0.0是可以的
	//float a = 0.0;
	//if (a == 0.0) cout << "a == 0.0" << endl;
	//if (0 == a) cout << "0 == a" << endl;
//	return 0;
//}