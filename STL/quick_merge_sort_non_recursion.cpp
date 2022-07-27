#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int qsort(vector<int>& arr, int left, int right) {
	int pivot = arr[left]; // 参考元素，可以理解为隔板
	int i = left, j = right;
	// 循环找比隔板小的在右边的数，比隔板大但在左边的数，交换位置，这样比隔板小的就到了隔板左边，比隔板大的就都到了隔板右边
	while (i < j) {
		while (i < j && arr[j] >= pivot) --j; // 这一句一定要在前面！！！先找到第一个比pivot小的再说，因为可能pivot刚好是最小的，如果先移动了i，会造成pivot位置被错换到第二位
		while (i < j && arr[i] <= pivot) ++i;
		swap(arr[i], arr[j]);
	}
	// 因为隔板还在数组最左边，所以要把隔板给换到正确的位置上
	swap(arr[i], arr[left]);
	return i; // 返回隔板处的索引作为下次入栈起点终点的参考
}

void quickSort_non_recur(vector<int>&arr) {
	stack<int>stk;
	int n = arr.size()-1;
	if (n == 0) return;
	// 其实就是将递归改成栈模拟，先把数组始末入栈，然后开始循环即可
	stk.emplace(n);
	stk.emplace(0);
	while (!stk.empty()) {
		int left = stk.top(); stk.pop();
		int right = stk.top(); stk.pop();
		int mid = qsort(arr, left, right);
		if (right > mid + 1) {
			stk.emplace(right);
			stk.emplace(mid + 1);
		}
		if (left < mid-1) {
			stk.emplace(mid-1);
			stk.emplace(left);
		}
	}
}

void print(vector<int>& arr) {
	for (const int& num : arr) {
		cout << num << " ";
	}
	cout << endl;
}
int main() {
	vector<int>arr(10);
	for (int i = 0; i < 10; ++i) arr[i] = rand() % 20;
	print(arr);
	quickSort_non_recur(arr); // 排序并对比排序前后数组
	print(arr);
	return 0;
}