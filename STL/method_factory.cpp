#include<iostream>
using namespace std;

/*
	工厂方法模式
	1.构建产品基类，派生类重写基类虚函数实现具体产品的功能
	2.构建工厂基类，派生类重写基类虚函数实现生产不同产品
	3.客户端代码直接生成对应的工厂类，然后调用工厂类的方法生成产品
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

class Factory {
public:
	virtual Caculator* create_factory() = 0;
};

class AddFactory : public Factory {
public:
	Caculator* create_factory() {
		return new Add();
	}
};

class MinusFactory : public Factory {
public:
	Caculator* create_factory() {
		return new Minus();
	}
};

class MultiplyFactory : public Factory {
public:
	Caculator* create_factory() {
		return new Multiply();
	}
};

class DivideFactory : public Factory {
public:
	Caculator* create_factory() {
		return new Divide();
	}
};

//int main() {
//	AddFactory addFactory;
//	Caculator* add = addFactory.create_factory();
//	cout << add->caculate(1,3) << endl;
//	delete add;
//	return 0;
//}