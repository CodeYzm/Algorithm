#include<iostream>
using namespace std;
/*
	场景：租房子，组成：房东，中介代理，租客
*/

// 租房子抽象基类
class RentHouse {
public:
	virtual void rentHouse() = 0;
};

// 房东
class LandLord : public RentHouse {
private:
	string tenant; // 租客
public:
	LandLord(const string& _tenant):tenant(_tenant) {
	
	}
	void rentHouse() {
		cout << "房东 租房子给 " << tenant << endl;
	}
};

// 中介
class Proxy : public RentHouse {
private:
	LandLord* landlord;

	void manageHouse() {
		cout << "中介代理管理" << endl;
	}
public:
	Proxy(const string& _tenant) {
		landlord = new LandLord(_tenant);
	}
	~Proxy() {
		delete landlord;
		landlord = nullptr;
	}
	void rentHouse() {
		cout << "中介代理租房" << endl;
		landlord->rentHouse();
		manageHouse();
	}

};

//int main() {
//	string tenant = "YZM";
//	Proxy* pxy = new Proxy(tenant);
//	pxy->rentHouse();
//	delete pxy;
//	pxy = nullptr;
//	return 0;
//}