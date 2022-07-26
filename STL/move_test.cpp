#include<iostream>
using namespace std;

class Data { // �����࣬���������ƶ���������ƣ�ʡȥ�����ݿ�����������Ŀ���
public:
	Data() { cout << "Data() Ĭ�Ϲ���" << endl;}
	Data(const Data& src) { cout << "Data() ��������" << endl; }
};

class A { // ִ���࣬�����ƶ����캯�����ƶ���ֵ�����
private:
	Data* data; // �����ݳ�ԱΪData��ָ��
public:
	A(): data(new Data()){ cout << "A() Ĭ�Ϲ���" << endl;  }

	A(const A& src):data(new Data(*src.data)) {
		cout << "A() ��������" << endl;
	}

	A(A&& src)noexcept :data(src.data){
		src.data = nullptr;
		cout << "A() �ƶ�����" << endl;
	} 

	~A() {
		delete data;
	}

	A& operator=(const A& src){ // �������������
		if (&src == this) return *this;
		delete data;
		data = new Data(*src.data);
		cout << "A() ������ֵ" << endl;
		return *this;
	}

	A& operator=(A&& src)noexcept { // �������������
		if (&src == this) return *this;
		delete data;
		data = src.data;
		src.data = nullptr; // �ÿձ�֤�ƶ���Դ������������״̬�����ƶ���������Դ����
		cout << "A() �ƶ���ֵ" << endl;
		return *this;
	}

};
//int main() {
//	A a1;
//	cout << "=================" << endl;
//	A a2(a1);
//	cout << "=================" << endl;
//	A a3(move(a1));
//	cout << "=================" << endl;
//	A a4 = a3;
//	cout << "=================" << endl;
//	A a5 = move(a4);
//	return 0;
//}