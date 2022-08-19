#include<iostream>
using namespace std;

/*
	��������ģʽ
	1.������Ʒ���࣬��������д�����麯��ʵ�־����Ʒ�Ĺ���
	2.�����������࣬��������д�����麯��ʵ��������ͬ��Ʒ
	3.�ͻ��˴���ֱ�����ɶ�Ӧ�Ĺ����࣬Ȼ����ù�����ķ������ɲ�Ʒ
*/
class Caculator {
public:
	virtual int caculate(int a, int b) = 0; // ��Ϊ���麯�������������д
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