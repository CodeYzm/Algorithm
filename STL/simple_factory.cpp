#include<iostream>
using namespace std;

/*
	���ü��������࣬�������ࣺ�ӡ������ˡ�����ʵ�־��幦�ܣ�����ɹ���������û�����������ʵ��
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

// ������
class Factory {
public:
	// ����һ������ָ��ָ���������(��̬��ʵ��)
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
//	// ���鹦��
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
//	// �ͷ���Դ 
//	delete add;
//	delete minus;
//	delete multiply;
//	delete divide;
//	return 0;
//}