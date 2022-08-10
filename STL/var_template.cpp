#include<iostream>
#include<vector>
using namespace std;

// 1.变量模板
template<typename T>
static T pi;

// 2.constexpr包含多个语句
//constexpr int getNum(int num) {
//	for (int i = 0; i < 1; ++i) num -= 1;
//	if (num >= 0) return num;
//	return -num;
//}

// 3.auto返回值自动推导
auto auto_ret() {
	int num = 0;
	return num;
}

// 5.lambda表达式的两种拓展
void test_lambda() {
	int x = 5;
	// 5.1. y = x+1 利用捕获变量进行初始化 
	// 5.2. auto自动推断输入参数类型
	auto test = [y = x + 1](auto& a) {
		cout << "自动推导输入参数类型：" << a << endl;
		cout << "利用捕获变量初始化：" << y << endl;
		return;
	};
	int num = 10;
	test(num);
}

// exchange，用于完美转发，使用指定新值替换旧值
void test_exchange() {
	vector<int>test{1,2,3,4,5};
	cout << "exchange 之前：" << test.size() << endl;
	exchange(test, { 0,1,2,3 });
	cout << "exchange 之后：" << test.size() << endl;
}
//int main() {
//	//pi<int> = 3.14;
//	//cout << pi<int> << endl;
//
//	//cout << getNum(10) << endl;
//
//	//// 4.整形字面量
//	//int x = 0b10; // 4.1.二进制字面量
//	//int y = 2'3'1; // 4.2.数字分割符
//	//cout << x << endl;
//	//cout << y << endl;
//
//	//// 自动推导为int，4字节
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