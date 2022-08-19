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
		cout << "具体工作" << endl;
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
			cout << "创建线程" << i << endl;
		}
	}

	~threadPool() {
		isEnd.store(true);
		cond.notify_all(); // 唤醒所有线程，执行任务
		for (shared_ptr<thread>& thread : pthreads) {
			if (thread->joinable())
				cout << "线程回收" << endl;
				thread->join(); // 等待线程结束
		}
	}

	void add_task(T* task) {
		unique_lock<mutex>ulock(mtx);
		q.emplace(task);
		cout << "任务数：" << q.size() << endl;
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
			cout << "任务数：" << q.size() << endl;
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