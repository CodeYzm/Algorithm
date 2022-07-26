/*
	(1,5)���������������(1,8)�����������
	(1,8)���������������(1,5)�����������
*/
#include<iostream>
using namespace std;

// ԭʼ�����������rand(1,8)
int rand_8() { 
	return rand() % 8 + 1;
}

// ԭʼ�����������rand(1,5)
int rand_5() { 
	return rand() % 5 + 1;
}

// ����rand(1,5)����rand(1,8)
int rand_5_8() {
	while (true) {
		// (rand_5() - 1)����[0,1,2,3,4]
		// (rand_5() - 1) * 5����[0,5,10,15,20]
		// (rand_5() - 1) * 5 + (rand_5() - 1) �պ��ܹ�����[0,1,2,3,4,5,6,7,8,9,...,24]
		// ������Ĺؼ����ڣ�����rand(1,5)��˻���㹻�����ɢ���䣬����ɢ����պ��ܱ�rand(1,5)���
		int num = (rand_5() - 1) * 5 + rand_5() - 1;
		if (num <= 23) return num % 8 + 1; // ֻȡ��23��ԭ���ǻ��[0-7, 8-15, 16-23]����������Ϊ8�ĵȸ��ʵ�����
	}
	return -1;
}

// ����rand(1,8)����rand(1,5)
int rand_8_5() {
	// ����һ��ֱ��������6-8�Ĳ���
	while (true) {
		int num = rand_8();
		if (num <= 5) return num;
	}
	// ��������ͬrand_5_8()�����ó˷�������ɢ���䣬����rand_8���������������
	while (true) {
		int num = (rand_8() - 1) * 8 + rand_8() - 1;
		if (num <= 54) return num % 5 + 1;
	}
	return -1;
}

int main() {
	srand((unsigned)time(NULL));
	int count_8[8] = { 0,0,0,0,0,0,0,0 }; // ͳ��1-8���ֵ�Ƶ�Σ��۲��Ƿ�ֲ�����
	int count_5[5] = { 0,0,0,0,0 }; // ͳ��1-5���ֵ�Ƶ�Σ��۲��Ƿ�ֲ�����
	for (int i = 0; i < 10000; ++i) {
		++count_8[rand_5_8() - 1];
	}	
	for (int i = 0; i < 10000; ++i) {
		++count_5[rand_8_5() - 1];
	}
	for (int i = 0; i < 8; ++i) {
		cout << i + 1 << " : " << count_8[i] << endl;
	}
	cout << "==========================" << endl;
	for (int i = 0; i < 5; ++i) {
		cout << i + 1 << " : " << count_5[i] << endl;
	}
	return 0;
}