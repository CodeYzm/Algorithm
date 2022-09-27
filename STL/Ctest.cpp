#include<iostream>
#include <unordered_map>
#include <map>
#include<vector>
using namespace std;

class A {
public:
	int a;
	// 重载类型转换运算符不能指定返回值
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
//	return 0;
//}


