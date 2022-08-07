#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void print(vector<int>& arr) {
	cout << arr.size() << endl;
	for (const int& num : arr) cout << num << ' ';
	cout << endl;
}

void discretization(vector<int>&arr) {
	// 临时数组
	vector<int>tmp = arr;
	// 排序
	sort(tmp.begin(), tmp.end());
	print(tmp);
	// 对每个元素，找到当前元素在排序数组中的位置并作为元素值赋值，+1表示是因为下标从0开始
	for (int& num : arr) num = lower_bound(tmp.begin(), tmp.end(), num) - tmp.begin() + 1;
}


//int main() {
//	vector<int>arr(20);
//	for (int i = 0; i < 20; ++i) arr[i] = rand() % 50;
//	print(arr);
//	discretization(arr);
//	print(arr);
//	return 0;
//}