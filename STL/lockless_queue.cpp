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

	// ����
	void lock() {
		bool expect = false;
		// 1. ���flag��ֵ������ֵ����������ֵ��ȣ���ô���µ�ֵ����flag������true
		// 2. ���flag��ֵ������ֵ��������ֵ����ȣ���ô��flag��ֵ����expect������false�����ÿ�ζ�Ҫ����expect
		// ���flag == false, compare����true,Ȼ���true��ֵ��flag������
		// flag == true��compare����false��expect�ᱻ��ֵһ�����µ�flagֵ
		while (!flag.compare_exchange_weak(expect, true)) {
			expect = false;
		}
	}

	// ����
	void unlock() {
		flag.store(false);
	}

private:
	CAS(const CAS&) = delete;
	CAS& operator=(const CAS&) = delete;
	atomic<bool> flag; // falseΪ����״̬ trueΪ����״̬
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
	// ��������
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