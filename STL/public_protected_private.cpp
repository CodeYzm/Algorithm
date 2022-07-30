#include<iostream>
using namespace std;

template<typename T> // struct������ģ��
struct A {
public:
	T data;
	~A() {
	
	}
};


class Person {
private:
	int id;
protected:
	int salary;
public:
	friend class Friend; // ��Ԫ��
	friend int visit(Person& p); // ��Ԫ����
	int age;
	Person() {}
	Person(int _id, int _salary, int _age):id(_id), salary(_salary), age(_age) { }
};

class Teacher :public Person {
public:
	Teacher() {
		// cout << id << endl; // ˽�����������಻�ɷ���
		cout << salary << endl;
		cout << age << endl;
	}
};

// ���ּ̳з�ʽ
class Worker :protected Person {
public:
	Worker() {
		cout << salary << endl;
	}
	
};

class Man :private Worker {
public:
	Man() {
		cout << salary << endl;
	}
};

class BigMan :public Man {
public:
	BigMan() {
		// cout << salary << endl;
	}
};

class Friend {
public:
	Friend() {
		
	}
	void visit(Person& p) {
		cout << p.age << endl;
	}
};

int visit(Person& p) {
	return p.id;
}


//int main() {
//	Person p;
//	cout << p.age << endl;
//	return 0;
//}