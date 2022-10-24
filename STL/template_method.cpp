#include<iostream>
using namespace std;

class Drink {
public:
	virtual ~Drink() {}
	void makeDrink() {
		addPowder();
		addWater();
		stir();
		changeTmp();
	}
protected:
	void addWater() {
		cout << "加入纯净水" << endl;
	}
	void stir() {
		cout << "搅拌均匀" << endl;
	}
private:
	virtual void addPowder() = 0;
	virtual void changeTmp() = 0;
};

class Cola:public Drink {
private:
	void addPowder() {
		cout << "加入可乐粉" << endl;
	}
	void changeTmp() {
		cout << "制冷" << endl;
	}
};

class Coffee :public Drink {
private:
	void addPowder() {
		cout << "加入咖啡粉" << endl;
	}
	void changeTmp() {
		cout << "加热" << endl;
	}
};

//int main() {
//	Drink* cola = new Cola();
//	Drink* coffee = new Coffee();
//	cola->makeDrink();
//	cout << "==============" << endl;
//	coffee->makeDrink();
//	delete cola;
//	delete coffee;
//	return 0;
//}