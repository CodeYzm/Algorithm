#include<iostream>
using namespace std;

class Data { // 数据类，用来体现移动构造的优势：省去了数据拷贝构造带来的开销
public:
	Data() { cout << "Data() 默认构造" << endl;}
	Data(const Data& src) { cout << "Data() 拷贝构造" << endl; }
};

class A { // 执行类，建立移动构造函数和移动赋值运算符
private:
	Data* data; // 类数据成员为Data类指针
public:
	A(): data(new Data()){ cout << "A() 默认构造" << endl;  }

	A(const A& src):data(new Data(*src.data)) {
		cout << "A() 拷贝构造" << endl;
	}

	A(A&& src)noexcept :data(src.data){
		src.data = nullptr;
		cout << "A() 移动构造" << endl;
	} 

	~A() {
		delete data;
	}

	A& operator=(const A& src){ // 返回类对象引用
		if (&src == this) return *this;
		delete data;
		data = new Data(*src.data);
		cout << "A() 拷贝赋值" << endl;
		return *this;
	}

	A& operator=(A&& src)noexcept { // 返回类对象引用
		if (&src == this) return *this;
		delete data;
		data = src.data;
		src.data = nullptr; // 置空保证移动后源对象进入可析构状态，但移动过后不能再源对象
		cout << "A() 移动赋值" << endl;
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