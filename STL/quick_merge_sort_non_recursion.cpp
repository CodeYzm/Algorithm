#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int qsort(vector<int>& arr, int left, int right) {
	int pivot = arr[left]; // �ο�Ԫ�أ��������Ϊ����
	int i = left, j = right;
	// ѭ���ұȸ���С�����ұߵ������ȸ��������ߵ���������λ�ã������ȸ���С�ľ͵��˸�����ߣ��ȸ����ľͶ����˸����ұ�
	while (i < j) {
		while (i < j && arr[j] >= pivot) --j; // ��һ��һ��Ҫ��ǰ�棡�������ҵ���һ����pivotС����˵����Ϊ����pivot�պ�����С�ģ�������ƶ���i�������pivotλ�ñ������ڶ�λ
		while (i < j && arr[i] <= pivot) ++i;
		swap(arr[i], arr[j]);
	}
	// ��Ϊ���廹����������ߣ�����Ҫ�Ѹ����������ȷ��λ����
	swap(arr[i], arr[left]);
	return i; // ���ظ��崦��������Ϊ�´���ջ����յ�Ĳο�
}

void quickSort_non_recur(vector<int>&arr) {
	stack<int>stk;
	int n = arr.size()-1;
	if (n == 0) return;
	// ��ʵ���ǽ��ݹ�ĳ�ջģ�⣬�Ȱ�����ʼĩ��ջ��Ȼ��ʼѭ������
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

void merge(vector<int>& arr, int left, int mid, int right) {
	if (left >= right) return;
	vector<int>tmp(right - left + 1);
	int i = left, j = mid + 1, idx = -1;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			tmp[++idx] = arr[i];
			++i;
		}
		else {
			tmp[++idx] = arr[j];
			++j;
		} 
	}
	while (i <= mid) tmp[++idx] = arr[i++];
	while (j <= right) tmp[++idx] = arr[j++];
	for (i = left; i <= right; ++i) arr[i] = tmp[i - left];
}

void mergeSort_non_recur(vector<int>& arr) {
	stack<int>stk;
	int n = arr.size() - 1;
	// ���ݹ����г���ѭ��[1, 2, 4, ...]
	for (int i = 1; i <= n; i <<= 1) {
		int left = 0, mid = left + i - 1, right = mid + i;
		// �ϲ�����ͬ�ȳ������У�����������
		while (right <= n) {
			merge(arr, left, mid, right);
			// ����һ����������������һ���±꿪ʼ
			left = right + 1;
			mid = left + i - 1;
			right = mid + i;
		}
		// ���� right = mid + i ����Խ������
		if (right > n && left <= n && mid <= n) merge(arr, left, mid, n);
	}
}

//void print(vector<int>& arr) {
//	for (const int& num : arr) {
//		cout << num << " ";
//	}
//	cout << endl;
//}

//int main() {
//	vector<int>arr(10);
//	for (int i = 0; i < 10; ++i) arr[i] = rand() % 20;
//	print(arr);
//	//quickSort_non_recur(arr); // ���򲢶Ա�����ǰ������
//	mergeSort_non_recur(arr);
//	print(arr);
//	return 0;
//}