#include<iostream>
#include <unordered_map>
#include <map>
#include<vector>
using namespace std;

class A {
public:
	int a;
	// ��������ת�����������ָ������ֵ
	operator int() {
		return this->a;
	}
};

//int main() {
//	A a;
//	a.a = 10;
//	int b = a.operator int();
//	int c = int(a);
//	cout << b << endl;
//	char s[3] = { 'h','e' ,'\0'}; // ��������飬�ڲ���������ֹ��
//	cout << strlen(s) << endl;
//	return 0;
//}


