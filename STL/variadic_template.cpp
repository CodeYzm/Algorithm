#include<iostream>
using namespace std;

/*
   可变参数模板：实现模板函数或模板类的参数数目可变
*/
template<typename T, typename ...Args> //...声明参数包
void print(T t, Args... rest) {
	cout << t << " ";
	cout << "参数包中参数个数：" << sizeof...(rest) << endl; //sizeof...运算符查看参数包有几个参数
}


//int main() {
//	print(1, 'a', "abc");
//	print(1, 2, "abc");
//	print(1, 2, "abc", 4);
//	return 0;
//}