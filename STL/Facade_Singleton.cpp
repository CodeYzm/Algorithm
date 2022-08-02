#include<iostream>
using namespace std;
/*
	���ģʽ(Facade Pattern)������
		�����������Ա������Ʒ�����ϵ�����������Ҫ�������ӵ����̣�������ֻ��Ҫͨ���Ա���������µ����ɣ�����Ҫ��ע��Ʒ���ڲ�����ת����
		�������ݴ����ͷ�����ȷ�ϡ��������͵�
*/

// �������ݴ���
class Data {
public:
	void run() {
		cout << "���������ύ����" << endl;
	}
};

// �ͷ�����ȷ��
class Check {
public:
	void run() {
		cout << "�ͷ�����ȷ��" << endl;
	}
};

// ��������
class Trans {
public:
	void run() {
		cout << "��������" << endl;
	}
};

// �ӿ��࣬�û�������Ʒ
class Buy {
private:
	Data* data;
	Check* check;
	Trans* trans;
	// ˽�л����캯����������������ֵ�������ֹ���ʵ������
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
		cout << "����" << endl;
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
		cout << "�������" << endl;
	}
};


//int main() {
//	Buy::getInstance().run();
//	return 0;
//}