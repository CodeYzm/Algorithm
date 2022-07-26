/*
	(1,5)随机数生成器构建(1,8)随机数生成器
	(1,8)随机数生成器构建(1,5)随机数生成器
*/
#include<iostream>
using namespace std;

// 原始随机数生成器rand(1,8)
int rand_8() { 
	return rand() % 8 + 1;
}

// 原始随机数生成器rand(1,5)
int rand_5() { 
	return rand() % 5 + 1;
}

// 利用rand(1,5)构造rand(1,8)
int rand_5_8() {
	while (true) {
		// (rand_5() - 1)生成[0,1,2,3,4]
		// (rand_5() - 1) * 5生成[0,5,10,15,20]
		// (rand_5() - 1) * 5 + (rand_5() - 1) 刚好能够生成[0,1,2,3,4,5,6,7,8,9,...,24]
		// 这类题的关键在于，利用rand(1,5)相乘获得足够大的离散区间，且离散区间刚好能被rand(1,5)填充
		int num = (rand_5() - 1) * 5 + rand_5() - 1;
		if (num <= 23) return num % 8 + 1; // 只取到23，原因是获得[0-7, 8-15, 16-23]这三个长度为8的等概率的区间
	}
	return -1;
}

// 利用rand(1,8)构造rand(1,5)
int rand_8_5() {
	// 方案一：直接舍弃掉6-8的部分
	while (true) {
		int num = rand_8();
		if (num <= 5) return num;
	}
	// 方案二：同rand_5_8()，采用乘法构建离散区间，再用rand_8本身填补成连续区间
	while (true) {
		int num = (rand_8() - 1) * 8 + rand_8() - 1;
		if (num <= 54) return num % 5 + 1;
	}
	return -1;
}

int main() {
	srand((unsigned)time(NULL));
	int count_8[8] = { 0,0,0,0,0,0,0,0 }; // 统计1-8出现的频次，观察是否分布均匀
	int count_5[5] = { 0,0,0,0,0 }; // 统计1-5出现的频次，观察是否分布均匀
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