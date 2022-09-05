#include<iostream>
#include<vector>
#include<thread>
#include<atomic>
#include<queue>
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

class CAS {
public:
	CAS(){
		flag.store(false);
	}
	~CAS() {}

	void lock() {
		bool expect = false;
		while (!flag.compare_exchange_weak(expect, true)) {
			expect = false;
		}
	}

	void unlock() {
		flag.store(false);
	}
private:
	atomic<bool>flag;
	CAS& operator=(const CAS&) = delete;
	CAS(const CAS&) = delete;
};

template<class T>
class ThreadPool {
private:
	CAS mutex;
	vector<shared_ptr<thread>>threads;
	queue<T*>q;
	int max_task;
	bool is_end;
public:
	ThreadPool(int t_num = 5, int _max_task = 10):is_end(false), max_task(_max_task){
		for (int i = 0; i < t_num; ++i) {
			threads.push_back(make_shared<thread>(&ThreadPool::work, this));
			cout << "创建线程" << i << endl;
		}
	}

	~ThreadPool() {
		while (!q.empty()) {
			
		}
		is_end = true;
		for (shared_ptr<thread>& t : threads) {
			if (t->joinable()) {
				t->join();
				cout << "回收线程" << endl;
			}
		}
	}


	void attach(T* task) {
		mutex.lock();
		q.emplace(task);
		mutex.unlock();
	}

	void work() {
		while (!is_end) {
			mutex.lock();
			if (q.empty()) {
				mutex.unlock();
				continue;
			}
			T* task = q.front();q.pop();
			mutex.unlock();
			task->run();
		}
	}
};
//int main() {
//	ThreadPool<Work>*tp = new ThreadPool<Work>();
//	Work* a = new Work();
//	for (int i = 0; i < 10; ++i) {
//		tp->attach(a);
//		//Sleep(1000);
//	}
//	delete a;
//	delete tp;
//	return 0;
//}