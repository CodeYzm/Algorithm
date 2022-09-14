#include<iostream>
using namespace std;
/*
	�������ⷿ�ӣ���ɣ��������н�������
*/

// �ⷿ�ӳ������
class RentHouse {
public:
	virtual void rentHouse() = 0;
};

// ����
class LandLord : public RentHouse {
private:
	string tenant; // ���
public:
	LandLord(const string& _tenant):tenant(_tenant) {
	
	}
	void rentHouse() {
		cout << "���� �ⷿ�Ӹ� " << tenant << endl;
	}
};

// �н�
class Proxy : public RentHouse {
private:
	LandLord* landlord;

	void manageHouse() {
		cout << "�н�������" << endl;
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
		cout << "�н�����ⷿ" << endl;
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