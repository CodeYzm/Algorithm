#include<iostream>
#include<unordered_map>
#include<functional>
using namespace std;

class Noncopy {
public:
	Noncopy()= default;
	Noncopy(const Noncopy&) = delete;
	Noncopy& operator =(const Noncopy&) = delete;
};

template<typename Func>
class Event : public Noncopy {
public:
	// 注册观察者，支持左值和右值引用
	void attach(Func& f) {
		mp.emplace(++funcId, forward<Func>(f));
	}
	void attach(Func&& f) {
		mp.emplace(++funcId, forward<Func>(f));
	}
	void detach(int key) {
		mp.erase(key);
	}

	// 可变参数模板，消除接口变动的影响
	template<typename ...Args>
	void notify(Args&&... args) {
		for (auto& it : mp) {
			Func& f = it.second;
			f(forward<Args>(args)...);
		}
	}
private:
	unordered_map<int, Func>mp;
	int funcId;
	// 使用完美转发
	//template<typename F>
	//void assign(F&& f) {
	//	
	//}
};

class Observer1 {
public:
	void operator()(int state) {
		cout << "观察者1状态变更： " << state << endl;
	}
};

void Observer2(int state) {
	cout << "观察者2状态变更： " << state << endl;
}

auto Observer3 = [](int state) {
	cout << "观察者3状态变更： " << state << endl;
};


int main() {
	return 0;
}