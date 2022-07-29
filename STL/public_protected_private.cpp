#include<iostream>
using namespace std;

template<typename T>
struct A {

public:
	T data;
	~A() {
	
	}
private:


};


class Person {
private:
	int id;
protected:
	int salary;
public:
	friend Friend;
	int age;
	Person() {}
	Person(int _id, int _salary, int _age):id(_id), salary(_salary), age(_age) { }
};

class Teacher :public Person {
public:
	Teacher() {
		// cout << id << endl; // 私有数据派生类不可访问
		cout << salary << endl;
		cout << age << endl;
	}
};

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

int main() {
	Person p;
	cout << p.age << endl;
	return 0;
}