#include<iostream>
#include<unordered_map>
#include<functional>
using namespace std;


/*
	�Ľ��Ĺ۲���ģʽ��
		1.��֪ͨ�����ӿ���Ϊ�ɱ����ģ�壬�����˽ӿڱ仯������Ӱ��
		2.���ñ�׼��function���ͺ͹۲����ģ�廯������̳У�ʹ�۲��ߵ����͸������
*/


// ���ɿ����࣬��ʾ��ֹ���ù��캯�����������캯������ֵ�����
// ��Ϊ�۲����ֻ��һ������˲��ò��ɿ�������Ϊ���๹��۲������
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
	void attach(const Func& f) {
		mp.emplace(++funcId, forward<Func>(f));
		cout << "Func& ע��Id��" << funcId << endl;
	}
	void attach(Func&& f) {
		mp.emplace(++funcId, forward<Func>(f));
		cout << "Func&& ע��Id��" << funcId << endl;
	}

	// �Ƴ��۲���
	void detach(int key) {
		mp.erase(key);
		cout << "�Ƴ�IdΪ " << key << " �Ĺ۲���" << endl;
	}

	// �ɱ����ģ�壬�����ӿڱ䶯��Ӱ��
	template<typename ...Args>
	void notify(Args&&... args) {
		for (auto& it : mp) {
			Func& f = it.second;
			// ����ת����������
			f(forward<Args>(args)...);
		}
	}
private:
	unordered_map<int, Func>mp; // ʹ�ù�ϣ��洢���ö���
	int funcId; // ������۲��ߵ�Id
};

// ��ͬ�ĵ��ö�����Ϊ�۲���
class Observer1 {
public:
	void operator()(int state) { // �º���
		cout << "�۲���1״̬����� " << state << endl;
	}
};

void Observer2(int state) { // ȫ�ֺ���
	cout << "�۲���2״̬����� " << state << endl;
}

auto Observer3 = [](int state) { // ��������
	cout << "�۲���3״̬����� " << state << endl;
};

using func = std::function<void(int)>; // function��װ���ö��󣬲������

//int main() {
//	Event<func>event; // ��function��װ�ĵ��ö���ָ��ģ���������
//	event.attach(Observer1());
//	event.attach(Observer2);
//	event.attach(Observer3);
//	event.notify(3);
//	event.detach(3);
//	return 0;
//}