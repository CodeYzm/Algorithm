#include<iostream>
using namespace std;

/*
	假定一个场景，商品在不同的活动中，折扣力度不同，使用策略模式进行折扣力度的替换
*/

class CashStrategy {
public:
	virtual double acceptCash(int price) {
		return price; // 默认原价
	};
};


class ConcreteStrategy1 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.5; // 打5折
	}
};

class ConcreteStrategy2 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.7; // 打7折
	}
};

class ConcreteStrategy3 :public CashStrategy {
public:
	double acceptCash(int price) {
		return price * 0.9; // 打9折
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
//	cout << "原价 = " << price << endl;
//
//	CashContext* ct; 
//	ct = new CashContext(cs1);
//	cout << "活动1价 = " << ct->getResult(100) << endl;
//	delete cs1; delete ct;
//	ct = new CashContext(cs2);
//	cout << "活动2价 = " << ct->getResult(100) << endl;
//	delete cs2; delete ct;
//	ct = new CashContext(cs3);
//	cout << "活动3价 = " << ct->getResult(100) << endl;
//	delete cs3; delete ct;
//	return 0;
//}