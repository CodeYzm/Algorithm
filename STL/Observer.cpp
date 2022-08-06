#include<iostream>
#include<list>
using namespace std;

/*
	观察者模式/ 发布-订阅模式：主题/ 发布者的状态发生变化时，要通知所有观察者更新自己的状态

	适用场景：
		单个类对象的变化要设计所有相关类状态的场景，比如：作者更新作品时要通知所有订阅了作品的粉丝
		当一个抽象模型有两个方面，其中一个方面依赖于另一方面。将这二者封装在独立的对象中以使它们可以各自独立的改变和复用
*/

// 观察者跟被观察主题的基类一定要先定义，否则在写实际的观察者需要用到主题成员的时候，会因为类未定义或声明无法使用
// 观察者抽象基类
class Observer {
public:
	virtual void update(int) = 0; // 更新观察者对被观察者状态的认知
};

// 被观察主题抽象基类
class Subject {
public:
	virtual void setState(int) = 0; // 设置状态
	virtual void attach(Observer*) = 0; // 添加观察者
	virtual void detach(Observer*) = 0; // 移除观察者
	virtual void notify() = 0; // 通知观察者
};

// 实际观察者1
class concreteObserver1 : public Observer {
private:
	Subject* subject;
public:
	// 在被观察者维护的链表中添加该观察者
	concreteObserver1(Subject* _subject){
		this->subject = _subject;
		this->subject->attach(this);
		cout << "注册观察者1" << endl;
	}

	void update(int val) {
		cout << "观察者1更新： " << val << endl;
	}
};

// 实际观察者2
class concreteObserver2 : public Observer {
private:
	Subject* subject;
public:
	concreteObserver2(Subject* _subject) {
		this->subject = _subject;
		this->subject->attach(this);
		cout << "注册观察者2" << endl;
	}

	void update(int val) {
		cout << "观察者2更新： " << val << endl;
	}
};


// 具体主题
class concreteSubject : public Subject {
private:
	list<Observer*>observers_list; // 维护一个观察者链表，以便更新状态时通知给每一个观察者
	int state;
public:
	void setState(int _state) {
		state = _state;
	}

	// 添加观察者
	void attach(Observer* _obs) {
		observers_list.emplace_back(_obs);
	}

	// 去除观察者
	void detach(Observer* _obs) {
		observers_list.remove(_obs);
	}

	// 提醒观察者
	void notify() {
		for (auto& ob : observers_list) {
			ob->update(state);
		}
	}
};

//int main() {
//	Subject *subj = new concreteSubject();
//	Observer* obs1 = new concreteObserver1(subj);
//	Observer* obs2 = new concreteObserver2(subj);
//	subj->setState(5);
//	subj->notify();
//	delete obs2;
//	delete obs1;
//	delete subj;
//	return 0;
//}