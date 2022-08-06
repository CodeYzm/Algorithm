#include<iostream>
using namespace std;
/*
	模板参数推断、引用折叠、完美转发
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
//	cout << "调用 print(T&)" << endl;
//}

template<typename T>
void print(T&& t) {
	f(t);
	f(forward<T>(t));
	cout << "调用 print(T&&)" << endl;
}

//int main() {
//	int i = 0;
//	int& a = i;
//	print(i);
//	print(a);
//	print(0);
//	return 0;
//}


