#include<iostream>
using namespace std;

/*VS默认对齐数是8字节， Linux为4字节*/

struct A {
	int a; // int 4字节，根据规则1，a存储范围0-3
	double b; // double 8字节，min(8,8) = 8, 根据规则2，b存储范围 8-15
	char c; // char 1字节，min(1,8) = 1，根据规则2，c存储范围 16
	// 目前结构体A存储范围0-16，总共17个字节
	// 由于A结构体内部最大元素类型占8个字节，根据规则3，结构体大小应该为8的整数倍，因此最终sizeof(A) = 3 * 8 = 24
};

struct B {
	int b; // 4字节，根据规则1，存储范围 0-3 
	A a;  // 根据规则3，结构体A内部最大的成员为8字节，对齐按8字节算，8的整数倍，8-31
	// 目前结构体A存储范围0-31，总共32个字节
	// 根据规则4，符合8的整数倍，因此最终结果sizeof(B) = 4 * 8 = 32
};
//int main() {
//    cout << sizeof(A) << endl;
//	cout << sizeof(B) << endl;
//	return 0;
//}