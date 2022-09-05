#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <atomic>
using namespace std;

int mutex = 0;
int lock = 1;
int unlock = 0;

class CAS {
public:
	CAS() : flag(false) {}

	// 上锁
	void lock() {
		bool expect = false;
		// 1. 如果flag的值（锁的值）和期望的值相等，那么将新的值赋给flag，返回true
		// 2. 如果flag的值（锁的值）和期望值不相等，那么将flag的值赋给expect，返回false，因此每次都要重置expect
		// 如果flag == false, compare返回true,然后把true赋值给flag，上锁
		// flag == true，compare返回false，expect会被赋值一个最新的flag值
		while (!flag.compare_exchange_weak(expect, true)) {
			expect = false;
		}
	}

	// 解锁
	void unlock() {
		flag.store(false);
	}

private:
	CAS(const CAS&) = delete;
	CAS& operator=(const CAS&) = delete;
	atomic<bool> flag; // false为解锁状态 true为上锁状态
};


class Thread {
public:
	Thread(function<void()> func) : func_(func) {}

	thread start() {
		thread t(func_);
		return t;
	}

private:
	function<void()> func_;
};

class ThreadPool {
public:

	void startPool(int poolSize) {
		for (int i = 0; i < poolSize; ++i) {
			pool_.push_back(new Thread(bind(&ThreadPool::runInPool, this, i)));
		}

		for (int i = 0; i < poolSize; ++i) {
			handler_.push_back(pool_[i]->start());
		}

		for (int i = 0; i < poolSize; ++i) {
			handler_[i].join();
		}
	}

private:
	// 工作函数
	void runInPool(int threadId) {
		mutex_.lock();
		cout << "Thread start! Thread Id:" << threadId << endl;
		mutex_.unlock();
	}

	vector<Thread*> pool_;
	vector<thread> handler_;

	CAS mutex_;
};


//int main() {
//
//	ThreadPool pool;
//	pool.startPool(10);
//
//	return 0;
//}