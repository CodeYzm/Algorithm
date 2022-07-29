#include<iostream>
using namespace std;

/*
	�������������ӵļ����������������мӼ��Ĺ���
	1.�����������Ӽ��������࣬��������д�����麯��ʵ�ּӼ�����
	2.���ó��󹤳��࣬�������ڲ��������麯����Ӧ�������Ӽ������������麯��
	3.�������幤���࣬ʵ�־���ļӷ��ͼ�����Ʒ���ӷ���Ʒ��ͼ�����Ʒ�඼�����������Ӽ�����������
*/

// ����������1
class Caculator1 {
public:
	virtual int caculate1(int a, int b) = 0; // ��Ϊ���麯�������������д
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

// ����������2
class Caculator2 {
public:
	virtual int caculate2(int a, int b) = 0; // ��Ϊ���麯�������������д
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

// ���󹤳��࣬�������Ӷ���������
class Factory {
public:
	virtual Caculator1* create_caculator1() = 0;
	virtual Caculator2* create_caculator2() = 0;
};

// ���幤���࣬���������������ӵļӷ���
class AddFactory : public Factory {
public:
	Caculator1* create_caculator1() {
		return new Add1();
	}
	Caculator2* create_caculator2() {
		return new Add2();
	}
};

// ���幤���࣬���������������ӵļ�����
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
	// �����������ӵļ������Ƿ����
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