#include<iostream>
using namespace std;
// https://blog.csdn.net/weixin_44178960/article/details/126212101?spm=1001.2014.3001.5502

template<typename T>
class Func {
public:
	Func(const T& _data) :data(_data) {}
	void operator()(T n) {
		cout << "仿函数输出：" << (n > data ? "大于" : "不大于") << endl;
	}
private:
	T data;
};


void test2(int n, Func<int>& fun) {
	fun(n);
}

//int main() {
//	int n = 20;
//	Func<int>func(20);
//	test2(n, func);
//	return 0;
//}