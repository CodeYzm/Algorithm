#include<iostream>
using namespace std;

class A {
public:
	void func1() {}
	void func2() {}
	virtual void func3() {}
};

void usage_of_shared_ptr() {
	
	// 1.创建shared_ptr
	// 推荐使用make_shared
	shared_ptr<int>sp1 = make_shared<int>(4);
	//shared_ptr<int>sp2 = shared_ptr<int>(new int(4));
	// 不要用同一个原始指针初始化多个智能指针
	int* p = new int(4);
	shared_ptr<int>sp2(p);
	shared_ptr<int>sp3(p);
	//cout << sp1 << endl;
	//cout << bool(sp1) << endl;

	// 2.资源管理权共享
	// 使用拷贝构造
	//shared_ptr<int>sp2(sp1);
	// 使用赋值运算符
	//shared_ptr<int>sp3 = sp1;
	//cout << sp2.use_count() << endl;
	//cout << bool(sp1) << endl;

	// 3.reset()
	// 无参数调用，引用计数清0，取消对资源的管理权
	sp1.reset();
	// 带参数调用，引用计数变为1，获得新的资源管理权
	sp1.reset(new int(1));

	// 4.判空
	//cout << sp1.use_count() << endl;
	//cout << (sp1 == nullptr) << endl;
	//cout << (!sp1) << endl;
	//cout << (sp1 == NULL) << endl;

	// 5.自定义删除器
	//auto deletor = [](int* p) {
	//	cout << "使用自定义删除器析构" << endl;
	//	delete[]p;
	//};
	//int* p2 = new int[2];
	//shared_ptr<int[]>sp4(p2,deletor);

	weak_ptr<int>sp9(sp1);
	sp9.
}

int main() {
	usage_of_shared_ptr();
	return 0;
}