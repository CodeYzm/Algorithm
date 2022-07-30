#include<iostream>
using namespace std;

/*
	假设有两种牌子的计算器，计算器都有加减的功能
	1.设置两种牌子计算器基类，派生类重写基类虚函数实现加减功能
	2.设置抽象工厂类，工厂类内部有两个虚函数对应两种牌子计算器的生产虚函数
	3.构建具体工厂类，实现具体的加法和减法产品，加法产品类和减法产品类都包含两种牌子计算器的生产
*/

// 计算器牌子1
class Caculator1 {
public:
	virtual int caculate1(int a, int b) = 0; // 设为纯虚函数，子类必须重写
};

class Add1 : public Caculator1 {
public:
	int caculate1(int a, int b) {
		cout << "China Add" << endl;
		return a + b;
	}
};

class Minus1 : public Caculator1 {
public:
	int caculate1(int a, int b) {
		cout << "China Minus" << endl;
		return a - b;
	}
};

// 计算器牌子2
class Caculator2 {
public:
	virtual int caculate2(int a, int b) = 0; // 设为纯虚函数，子类必须重写
};
class Add2 : public Caculator2 {
public:
	int caculate2(int a, int b) {
		cout << "USA Add" << endl;
		return a + b;
	}
};

class Minus2 : public Caculator2 {
public:
	int caculate2(int a, int b) {
		cout << "USA Minus" << endl;
		return a - b;
	}
};

// 抽象工厂类，两种牌子都可以生产
class Factory {
public:
	virtual Caculator1* create_caculator1() = 0;
	virtual Caculator2* create_caculator2() = 0;
};

// 具体工厂类，负责生产两种牌子的加法器
class AddFactory : public Factory {
public:
	Caculator1* create_caculator1() {
		return new Add1();
	}
	Caculator2* create_caculator2() {
		return new Add2();
	}
};

// 具体工厂类，负责生产两种牌子的减法器
class MinusFactory : public Factory {
public:
	Caculator1* create_caculator1() {
		return new Minus1();
	}
	Caculator2* create_caculator2() {
		return new Minus2();
	}
};


int main() {
	// 看看两个牌子的计算器是否可用
	AddFactory add_factory;
	Caculator1* add1 = add_factory.create_caculator1();
	Caculator2* add2 = add_factory.create_caculator2();
	add1->caculate1(1,2);
	add2->caculate2(1, 2);
	MinusFactory minus_factory;
	Caculator1* minus1 = minus_factory.create_caculator1();
	Caculator2* minus2 = minus_factory.create_caculator2();
	minus1->caculate1(1, 2);
	minus2->caculate2(1, 2);
	delete add1; delete add2; delete minus1; delete minus2;
	return 0;
}