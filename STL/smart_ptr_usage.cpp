#include<iostream>
using namespace std;

class A {
public:
	void func1() {}
	void func2() {}
	virtual void func3() {}
};

void usage_of_shared_ptr() {
	
	// 1.����shared_ptr
	// �Ƽ�ʹ��make_shared
	shared_ptr<int>sp1 = make_shared<int>(4);
	//shared_ptr<int>sp2 = shared_ptr<int>(new int(4));
	// ��Ҫ��ͬһ��ԭʼָ���ʼ���������ָ��
	int* p = new int(4);
	shared_ptr<int>sp2(p);
	shared_ptr<int>sp3(p);
	//cout << sp1 << endl;
	//cout << bool(sp1) << endl;

	// 2.��Դ����Ȩ����
	// ʹ�ÿ�������
	//shared_ptr<int>sp2(sp1);
	// ʹ�ø�ֵ�����
	//shared_ptr<int>sp3 = sp1;
	//cout << sp2.use_count() << endl;
	//cout << bool(sp1) << endl;

	// 3.reset()
	// �޲������ã����ü�����0��ȡ������Դ�Ĺ���Ȩ
	sp1.reset();
	// ���������ã����ü�����Ϊ1������µ���Դ����Ȩ
	sp1.reset(new int(1));

	// 4.�п�
	//cout << sp1.use_count() << endl;
	//cout << (sp1 == nullptr) << endl;
	//cout << (!sp1) << endl;
	//cout << (sp1 == NULL) << endl;

	// 5.�Զ���ɾ����
	//auto deletor = [](int* p) {
	//	cout << "ʹ���Զ���ɾ��������" << endl;
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