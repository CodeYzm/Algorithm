#include<iostream>
using namespace std;
/*
	ģ������ƶϡ������۵�������ת��
*/

void f(int& n) {
	cout << "f(int&)" << endl;
}

void f(int&& n) {
	cout << "f(int&&)" << endl;
}

//template<typename T>
//void print(T& t) {
//	f(t);
//	f(forward<T>(t));
//	cout << "���� print(T&)" << endl;
//}

template<typename T>
void print(T&& t) {
	f(t);
	f(forward<T>(t));
	cout << "���� print(T&&)" << endl;
}

//int main() {
//	int i = 0;
//	int& a = i;
//	print(i);
//	print(a);
//	print(0);
//	return 0;
//}


