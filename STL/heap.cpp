#include<iostream>
#include<vector>
#include<algorithm>
#include <memory>
using namespace std;

void adjustHeap(vector<int>& arr, int idx, int n) {
	int left = idx << 1 + 1, right = idx << 1 + 2;
	int newIdx = idx;
	if (left < n && arr[left] < arr[newIdx]) newIdx = left;
	if (right < n && arr[right] < arr[newIdx]) newIdx = right;
	if (idx != newIdx) {
		swap(arr[idx], arr[newIdx]);
		adjustHeap(arr, newIdx, n);
	}
}
void buildHeap(vector<int>&arr, int n) {
	for (int i = (n >> 1) - 1; i >= 0; --i) {
		adjustHeap(arr, i, n);
	}
	//for (int i = n - 1; i > 0; --i) {
	//	swap(arr[i], arr[0]);
	//	adjustHeap(arr, 0, i);
	//}
}

//int main() {
//	shared_ptr<int> ptr_1 = make_shared<int>(1);
//	cout << *ptr_1 << endl;
//	return 0;
//}