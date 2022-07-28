#include<iostream>
using namespace std;
class B; // 前置声明

class A {
public:
	shared_ptr<B> m_b;
	// weak_ptr<B> m_b; // 方法一：通过weak_ptr弱引用解决
};

class B {
public:
	shared_ptr<A> m_a;
};

// 循环引用示例
void circular_reference() {
	//shared_ptr<A> a(new A());
	//shared_ptr<B> b(new B());
	shared_ptr<A> a = make_shared<A>();
	shared_ptr<B> b = make_shared<B>();
	a->m_b = b;
	b->m_a = a;
	// a->m_b.reset(); // 方法二：通过reset其中一个成员指针解决(没有意义)
	cout << a.use_count() << endl;
	cout << b.use_count() << endl;
}

int main() {
	circular_reference();
	return 0;
}