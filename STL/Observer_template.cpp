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
	// ע��۲��ߣ�֧����ֵ����ֵ����
	void attach(Func& f) {
		mp.emplace(++funcId, forward<Func>(f));
	}
	void attach(Func&& f) {
		mp.emplace(++funcId, forward<Func>(f));
	}
	void detach(int key) {
		mp.erase(key);
	}

	// �ɱ����ģ�壬�����ӿڱ䶯��Ӱ��
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
	// ʹ������ת��
	//template<typename F>
	//void assign(F&& f) {
	//	
	//}
};

class Observer1 {
public:
	void operator()(int state) {
		cout << "�۲���1״̬����� " << state << endl;
	}
};

void Observer2(int state) {
	cout << "�۲���2״̬����� " << state << endl;
}

auto Observer3 = [](int state) {
	cout << "�۲���3״̬����� " << state << endl;
};


int main() {
	return 0;
}