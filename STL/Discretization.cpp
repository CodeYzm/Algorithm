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
	// ��ʱ����
	vector<int>tmp = arr;
	// ����
	sort(tmp.begin(), tmp.end());
	print(tmp);
	// ��ÿ��Ԫ�أ��ҵ���ǰԪ�������������е�λ�ò���ΪԪ��ֵ��ֵ��+1��ʾ����Ϊ�±��0��ʼ
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