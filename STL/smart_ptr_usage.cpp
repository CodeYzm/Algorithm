#include<iostream>
using namespace std;

void usage_of_shared_ptr() {
	
	// 1.����shared_ptr
	// �Ƽ�ʹ��make_shared
	//shared_ptr<int>sp1 = make_shared<int>(4);
	//shared_ptr<int>sp2 = shared_ptr<int>(new int(4));
	// ��Ҫ��ͬһ��ԭʼָ���ʼ���������ָ��
	//int* p = new int(4);
	//shared_ptr<int>sp2(p);
	//shared_ptr<int>sp3(p);
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
	//sp1.reset();
	// ���������ã����ü�����Ϊ1������µ���Դ����Ȩ
	//sp1.reset(new int(1));

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

	//weak_ptr<int>wp1(sp1);
	//sp1 = wp1.lock();
	//cout << sp1.use_count() << endl;
	//sp1.reset();
	//cout << wp1.expired() << endl;

	unique_ptr<int>up(new int(2));
	unique_ptr<int>up1 = make_unique<int>(1);

	//cout << *up1 << endl;
	//cout << *(up1.get()) << endl;
	//unique_ptr<int>up2 = move(up1);
	//cout << *up2 << endl;
	//unique_ptr<int>up3(move(up2));
	//cout << *up3 << endl;

	//int* p = up1.release();
	//cout << *up1 << endl;
	//cout << *p << endl;

	//up.swap(up1);
	//cout << *up << endl;


	int* p = new int(3);
	up1.reset(p);
	cout << *up1 << endl;
}

//int main() {
//	usage_of_shared_ptr();
//	return 0;
//}