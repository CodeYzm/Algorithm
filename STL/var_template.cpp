#include<iostream>
#include<vector>
using namespace std;

// 1.����ģ��
template<typename T>
static T pi;

// 2.constexpr����������
//constexpr int getNum(int num) {
//	for (int i = 0; i < 1; ++i) num -= 1;
//	if (num >= 0) return num;
//	return -num;
//}

// 3.auto����ֵ�Զ��Ƶ�
auto auto_ret() {
	int num = 0;
	return num;
}

// 5.lambda���ʽ��������չ
void test_lambda() {
	int x = 5;
	// 5.1. y = x+1 ���ò���������г�ʼ�� 
	// 5.2. auto�Զ��ƶ������������
	auto test = [y = x + 1](auto& a) {
		cout << "�Զ��Ƶ�����������ͣ�" << a << endl;
		cout << "���ò��������ʼ����" << y << endl;
		return;
	};
	int num = 10;
	test(num);
}

// exchange����������ת����ʹ��ָ����ֵ�滻��ֵ
void test_exchange() {
	vector<int>test{1,2,3,4,5};
	cout << "exchange ֮ǰ��" << test.size() << endl;
	exchange(test, { 0,1,2,3 });
	cout << "exchange ֮��" << test.size() << endl;
}
//int main() {
//	//pi<int> = 3.14;
//	//cout << pi<int> << endl;
//
//	//cout << getNum(10) << endl;
//
//	//// 4.����������
//	//int x = 0b10; // 4.1.������������
//	//int y = 2'3'1; // 4.2.���ַָ��
//	//cout << x << endl;
//	//cout << y << endl;
//
//	//// �Զ��Ƶ�Ϊint��4�ֽ�
//	//cout << sizeof(auto_ret()) << endl;
//
//
//	// test_lambda();
//
//	//test_exchange();
//	char ch[] = "abc";
//	string ch1 = "abc";
//	cout << sizeof(ch) << strlen(ch) << endl;
//	cout << sizeof(ch1)  << endl;
//	return 0;
//}