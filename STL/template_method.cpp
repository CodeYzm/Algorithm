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
		cout << "���봿��ˮ" << endl;
	}
	void stir() {
		cout << "�������" << endl;
	}
private:
	virtual void addPowder() = 0;
	virtual void changeTmp() = 0;
};

class Cola:public Drink {
private:
	void addPowder() {
		cout << "������ַ�" << endl;
	}
	void changeTmp() {
		cout << "����" << endl;
	}
};

class Coffee :public Drink {
private:
	void addPowder() {
		cout << "���뿧�ȷ�" << endl;
	}
	void changeTmp() {
		cout << "����" << endl;
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