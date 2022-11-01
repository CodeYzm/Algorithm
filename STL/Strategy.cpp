#include<iostream>
using namespace std;

/*
	�ٶ�һ����������Ʒ�ڲ�ͬ�Ļ�У��ۿ����Ȳ�ͬ��ʹ�ò���ģʽ�����ۿ����ȵ��滻
*/

class CashStrategy {
public:
	virtual double acceptCash(int price) {
		return price; // Ĭ��ԭ��
	};
};


class ConcreteStrategy1 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.5; // ��5��
	}
};

class ConcreteStrategy2 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.7; // ��7��
	}
};

class ConcreteStrategy3 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.9; // ��9��
	}
};

class CashContext {
private:
	CashStrategy* cs;
public:
	CashContext(CashStrategy* _cs) :cs(_cs){}
	double getResult(int price) {
		return cs->acceptCash(price);
	}
};



//int main() {
//	CashStrategy* cs1 = new ConcreteStrategy1();
//	CashStrategy* cs2 = new ConcreteStrategy2();
//	CashStrategy* cs3 = new ConcreteStrategy3();
//	
//	int price = 100;
//	cout << "ԭ�� = " << price << endl;
//
//	CashContext* ct; 
//	ct = new CashContext(cs1);
//	cout << "�1�� = " << ct->getResult(100) << endl;
//	delete cs1; delete ct;
//	ct = new CashContext(cs2);
//	cout << "�2�� = " << ct->getResult(100) << endl;
//	delete cs2; delete ct;
//	ct = new CashContext(cs3);
//	cout << "�3�� = " << ct->getResult(100) << endl;
//	delete cs3; delete ct;
//	return 0;
//}