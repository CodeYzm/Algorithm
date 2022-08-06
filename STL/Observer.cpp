#include<iostream>
#include<list>
using namespace std;

/*
	�۲���ģʽ/ ����-����ģʽ������/ �����ߵ�״̬�����仯ʱ��Ҫ֪ͨ���й۲��߸����Լ���״̬

	���ó�����
		���������ı仯Ҫ������������״̬�ĳ��������磺���߸�����ƷʱҪ֪ͨ���ж�������Ʒ�ķ�˿
		��һ������ģ�����������棬����һ��������������һ���档������߷�װ�ڶ����Ķ�������ʹ���ǿ��Ը��Զ����ĸı�͸���
*/

// �۲��߸����۲�����Ļ���һ��Ҫ�ȶ��壬������дʵ�ʵĹ۲�����Ҫ�õ������Ա��ʱ�򣬻���Ϊ��δ����������޷�ʹ��
// �۲��߳������
class Observer {
public:
	virtual void update(int) = 0; // ���¹۲��߶Ա��۲���״̬����֪
};

// ���۲�����������
class Subject {
public:
	virtual void setState(int) = 0; // ����״̬
	virtual void attach(Observer*) = 0; // ��ӹ۲���
	virtual void detach(Observer*) = 0; // �Ƴ��۲���
	virtual void notify() = 0; // ֪ͨ�۲���
};

// ʵ�ʹ۲���1
class concreteObserver1 : public Observer {
private:
	Subject* subject;
public:
	// �ڱ��۲���ά������������Ӹù۲���
	concreteObserver1(Subject* _subject){
		this->subject = _subject;
		this->subject->attach(this);
		cout << "ע��۲���1" << endl;
	}

	void update(int val) {
		cout << "�۲���1���£� " << val << endl;
	}
};

// ʵ�ʹ۲���2
class concreteObserver2 : public Observer {
private:
	Subject* subject;
public:
	concreteObserver2(Subject* _subject) {
		this->subject = _subject;
		this->subject->attach(this);
		cout << "ע��۲���2" << endl;
	}

	void update(int val) {
		cout << "�۲���2���£� " << val << endl;
	}
};


// ��������
class concreteSubject : public Subject {
private:
	list<Observer*>observers_list; // ά��һ���۲��������Ա����״̬ʱ֪ͨ��ÿһ���۲���
	int state;
public:
	void setState(int _state) {
		state = _state;
	}

	// ��ӹ۲���
	void attach(Observer* _obs) {
		observers_list.emplace_back(_obs);
	}

	// ȥ���۲���
	void detach(Observer* _obs) {
		observers_list.remove(_obs);
	}

	// ���ѹ۲���
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