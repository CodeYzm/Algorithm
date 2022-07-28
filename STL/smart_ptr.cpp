#include<iostream>
using namespace std;
class B; // ǰ������

class A {
public:
	shared_ptr<B> m_b;
	// weak_ptr<B> m_b; // ����һ��ͨ��weak_ptr�����ý��
};

class B {
public:
	shared_ptr<A> m_a;
};

// ѭ������ʾ��
void circular_reference() {
	//shared_ptr<A> a(new A());
	//shared_ptr<B> b(new B());
	shared_ptr<A> a = make_shared<A>();
	shared_ptr<B> b = make_shared<B>();
	a->m_b = b;
	b->m_a = a;
	// a->m_b.reset(); // ��������ͨ��reset����һ����Աָ����(û������)
	cout << a.use_count() << endl;
	cout << b.use_count() << endl;
}

int main() {
	circular_reference();
	return 0;
}