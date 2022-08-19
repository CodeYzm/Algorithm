#include<iostream>
#include<cstdio>
#include<mutex>
#include<queue>
#include<Windows.h>
#include<condition_variable>
using namespace std;
static mutex mtx;
static condition_variable cv;
static queue<int>q;

class A {
public:
	//const A* f(const int d) {
	//	return this;
	//}
	//A f(const int& d)const {
	//	return *this;
	//}
	//A& f(int a, int b = 50) {
	//	cout << a << endl;
	//	return *this;
	//}
	//void f(int& a)const {
	//	cout << a << endl;
	//}
};


void productor() {
	while (true) {
		Sleep(1000);
		unique_lock<mutex>ulock(mtx);
		int num = rand() % 20;
		q.push(num);
		cout << "������������" << num << "  Ŀǰ��Ʒ������" << q.size() << " ��" << endl;
		ulock.unlock();
		cv.notify_one();
	}
}

void consumer() {
	while (true) {
		Sleep(1000);
		unique_lock<mutex>ulock(mtx);
		while (q.empty()) cv.wait(ulock);
		int num = q.front();
		q.pop();
		cout << "���������ѣ�" << num << "  Ŀǰ��Ʒ������" << q.size() << " ��" << endl;
		ulock.unlock();
	}
}


//int main() {
//	thread t1(productor);
//	thread t2(consumer);
//	t1.join();
//	t2.join();
//	return 0;
//}