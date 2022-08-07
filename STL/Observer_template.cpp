#include<iostream>
#include<unordered_map>
#include<functional>
using namespace std;


/*
	改进的观察者模式：
		1.将通知函数接口设为可变参数模板，消除了接口变化带来的影响
		2.利用标准库function类型和观察对象模板化，代替继承，使观察者的类型更加灵活
*/


// 不可拷贝类，显示禁止调用构造函数、拷贝构造函数、赋值运算符
// 因为观察对象只有一个，因此采用不可拷贝类作为基类构造观察对象类
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
	void attach(const Func& f) {
		mp.emplace(++funcId, forward<Func>(f));
		cout << "Func& 注册Id：" << funcId << endl;
	}
	void attach(Func&& f) {
		mp.emplace(++funcId, forward<Func>(f));
		cout << "Func&& 注册Id：" << funcId << endl;
	}

	// 移除观察者
	void detach(int key) {
		mp.erase(key);
		cout << "移除Id为 " << key << " 的观察者" << endl;
	}

	// 可变参数模板，消除接口变动的影响
	template<typename ...Args>
	void notify(Args&&... args) {
		for (auto& it : mp) {
			Func& f = it.second;
			// 完美转发参数类型
			f(forward<Args>(args)...);
		}
	}
private:
	unordered_map<int, Func>mp; // 使用哈希表存储调用对象
	int funcId; // 分配给观察者的Id
};

// 不同的调用对象作为观察者
class Observer1 {
public:
	void operator()(int state) { // 仿函数
		cout << "观察者1状态变更： " << state << endl;
	}
};

void Observer2(int state) { // 全局函数
	cout << "观察者2状态变更： " << state << endl;
}

auto Observer3 = [](int state) { // 匿名函数
	cout << "观察者3状态变更： " << state << endl;
};

using func = std::function<void(int)>; // function包装调用对象，并起别名

//int main() {
//	Event<func>event; // 由function包装的调用对象指定模板参数类型
//	event.attach(Observer1());
//	event.attach(Observer2);
//	event.attach(Observer3);
//	event.notify(3);
//	event.detach(3);
//	return 0;
//}