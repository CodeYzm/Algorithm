#include<iostream>
#include<vector>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<atomic>
#include<Windows.h>
using namespace std;


class Work {
public:
	Work() {}
	~Work() {}
	void run() {
		cout << "���幤��" << endl;
		Sleep(100);
	}
};

template<class T>
class threadPool {
private:
	mutex mtx;
	condition_variable cond;
	int thread_num;
	atomic<bool> isEnd;
	vector<shared_ptr<thread>>pthreads;
	queue<T*>q;

public:
	threadPool(int _thread_num = 7) :thread_num(_thread_num), isEnd{false} {
		for (int i = 0; i < _thread_num; ++i) {
			pthreads.push_back(
				std::make_shared<thread>(&threadPool::do_task, this)
			);
			cout << "�����߳�" << i << endl;
		}
	}

	~threadPool() {
		isEnd.store(true);
		cond.notify_all(); // ���������̣߳�ִ������
		for (shared_ptr<thread>& thread : pthreads) {
			if (thread->joinable())
				cout << "�̻߳���" << endl;
				thread->join(); // �ȴ��߳̽���
		}
	}

	void add_task(T* task) {
		unique_lock<mutex>ulock(mtx);
		q.emplace(task);
		cout << "��������" << q.size() << endl;
		ulock.unlock();
		cond.notify_all();
	}

	void do_task() {
		while (!isEnd.load()) {
			unique_lock<mutex>ulock(mtx);
			//cond.wait(ulock, 
			//	[this] {
			//		return this->isEnd.load() || !q.empty();
			//	});
			cond.wait(ulock);
			if (this->isEnd.load() && q.empty()) return;
			if (q.empty()) continue;
			T* task = q.front();
			q.pop();
			cout << "��������" << q.size() << endl;
			ulock.unlock();
			task->run();
		}
	}

};



//int main() {
//	threadPool<Work>* tp = new threadPool<Work>();
//	Work* w = new Work();
//	for (int i = 0; i < 10; ++i) {
//		tp->add_task(w);
//		Sleep(1000);
//	}
//	delete w;
//	delete tp;
//	return 0;
//}