#pragma pack(1)
#include<iostream>
#include<cstdio>
using namespace std;


void test() {
	int i = 0, j = 0;
	int k = 8;
	if (++i > 0 || j++ > 0) ++k;
	cout << i << j << k;
}
struct A {
	int b;
	double a;
	char c;
};
//int main() {
//
//	//test();
//	cout << sizeof(A) << endl;
//	// cout << sizeof(B) << endl;
//	return 0;
//}