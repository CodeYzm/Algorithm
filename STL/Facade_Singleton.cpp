#include<iostream>
using namespace std;
/*
	外观模式(Facade Pattern)场景：
		假设我们在淘宝购物，物品从网上到我们手里需要经过复杂的流程，而我们只需要通过淘宝点击购买下单即可，不需要关注商品在内部的流转流程
		订单数据处理、客服订单确认、物流派送等
*/

// 订单数据处理
class Data {
public:
	void run() {
		cout << "订单数据提交处理" << endl;
	}
};

// 客服订单确认
class Check {
public:
	void run() {
		cout << "客服订单确认" << endl;
	}
};

// 物流派送
class Trans {
public:
	void run() {
		cout << "物流派送" << endl;
	}
};

// 接口类，用户购买商品
class Buy {
private:
	Data* data;
	Check* check;
	Trans* trans;
	// 私有化构造函数、析构函数、赋值运算符防止多个实例产生
	Buy() {
		data = new Data();
		check = new Check();
		trans = new Trans();
	}
	~Buy() {
		delete data;
		delete check;
		delete trans;
		data = nullptr;
		check = nullptr;
		trans = nullptr;
		cout << "析构" << endl;
	}
	Buy& operator=(const Buy&) = delete;
public:
	static Buy& getInstance() {
		static Buy buy;
		return buy;
	}

	void run() {
		data->run();
		check->run();
		trans->run();
		cout << "购物完成" << endl;
	}
};


//int main() {
//	Buy::getInstance().run();
//	return 0;
//}