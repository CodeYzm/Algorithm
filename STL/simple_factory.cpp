#include<iostream>
using namespace std;

/*
	设置计算器基类，由派生类：加、减、乘、除类实现具体功能，最后由工厂类根据用户输入生成类实例
*/ 

class Caculator {
public:
	virtual int caculate(int a, int b) = 0; // 设为纯虚函数，子类必须重写
};

class Add : public Caculator {
public:
	int caculate(int a, int b) {
		return a + b;
	}
};

class Minus : public Caculator {
public:
	int caculate(int a, int b) {
		return a - b;
	}
};

class Multiply : public Caculator {
public:
	int caculate(int a, int b) {
		return a * b;
	}
};

class Divide : public Caculator {
public:
	int caculate(int a, int b) {
		return a / b;
	}
};

// 工厂类
class Factory {
public:
	// 返回一个父类指针指向子类对象(多态的实现)
	Caculator* create_caculator(char ch) { 
		switch (ch) {
		case 'a':
			return new Add();
		case 'b':
			return new Minus();
		case 'c':
			return new Multiply();
		case 'd':
			return new Divide();
		default:
			cout << "ERROR" << endl;	
			return nullptr;
		}
	}
};

//int main() {
//	// 检验功能
//	int a = 10, b = 2;
//	Factory factory;
//	Caculator* add = factory.create_caculator('a');
//	Caculator* minus = factory.create_caculator('b');
//	Caculator* multiply = factory.create_caculator('c');
//	Caculator* divide = factory.create_caculator('d');
//	cout << add->caculate(a, b) << endl;
//	cout << minus->caculate(a, b) << endl;
//	cout << multiply->caculate(a, b) << endl;
//	cout << divide->caculate(a, b) << endl;
//	// 释放资源 
//	delete add;
//	delete minus;
//	delete multiply;
//	delete divide;
//	return 0;
//}