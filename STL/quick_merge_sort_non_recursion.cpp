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
	quickSort_non_recur(arr); // ���򲢶Ա�����ǰ������
	print(arr);
	return 0;
}