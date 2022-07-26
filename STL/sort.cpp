#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printArray(vector<int>&nums) {
	for (const int& num : nums) {
		cout << num << ' ';
	}
	cout << endl;
}
void bubbleSort(vector<int>&nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// ÿ��ѭ��������������n-i-1��λ��
		for (int j = 1; j < n-i; ++j) {
			if (nums[j - 1] > nums[j]) swap(nums[j], nums[j - 1]);
		}
	}
}

void selectSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// ÿ��ѭ����i+1 - n������һ����С��������i
		int minN = i;
		for (int j = i+1; j < n; ++j) {
			if (nums[j] < nums[minN]) minN = j;
		}
		swap(nums[minN], nums[i]);
	}
}

void merge(vector<int>& nums, vector<int>& arr, int left, int mid, int right) {
	int i = left, j = mid + 1;
	int start = left-1;
	while (i <= mid && j <= right) {
		arr[++start] = nums[i] < nums[j] ? nums[i++] : nums[j++];
	}
	// �ϲ�ʣ��Ԫ��
	while (i <= mid) arr[++start] = nums[i++];
	while (j <= right) arr[++start] = nums[j++];
	// ��ֵ��ԭ����
	while (left <= right) {
		nums[left] = arr[left];
		++left;
	}
}
void m_sort(vector<int>& nums, vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) >> 1;
		// �ݹ����
		m_sort(nums, arr, left, mid);
		m_sort(nums, arr, mid + 1, right);
		// ���һ��ݹ�ϲ�
		merge(nums, arr, left, mid, right);
	}
}
void mergeSort(vector<int>& nums) {
	int n = nums.size();
	vector<int>arr(n);
	m_sort(nums, arr, 0, n-1);
}

void q_sort(vector<int>& nums, int left, int right) {
	if (left < right) {
		int i = left, j = right;
		while (i < j) {
			while (i < j && nums[j] >= nums[left]) --j;
			while (i < j && nums[i] <= nums[left]) ++i;
			swap(nums[i], nums[j]);
		}
		swap(nums[i], nums[left]);
		q_sort(nums, left, i - 1);
		q_sort(nums, i + 1, right);
	}
}
void quickSort(vector<int>& nums) {
	int n = nums.size();
	q_sort(nums, 0, n-1);
}

void insertionSort(vector<int>& nums) {
	int n = nums.size();
	// �ӵڶ���Ԫ�ؿ�ʼ����
	for (int i = 1; i < n; ++i) {
		int num = nums[i];
		int j = i - 1;
		// ÿһ���ȵ�i+1��Ԫ�ش��Ԫ�ض��ᱻ���ƣ����С��Ԫ�ػᱻ���뵽ǰ��
		while (j >= 0 && nums[j] > num) {
			swap(nums[j], nums[j + 1]);
			--j;
		}
	}
}

void shellSort(vector<int>& nums) {
	int n = nums.size();
	// ȡ��ʼ����Ϊn/2 ��ÿ����������С1/2
	for (int inc = n >> 1; inc > 0; inc >>= 1) {
		// incΪ��������ı�����㣬��ΪĬ�ϵ�һ��Ԫ���������
		for (int i = inc; i < n; ++i) {
			int num = nums[i];
			// �����һ��Ԫ�رȵ�ǰԪ�ش󣬲��Ϻ���
			for (int j = i; j >= inc && num < nums[j - inc]; j -= inc) {
				swap(nums[j], nums[j - inc]);
			}
		}
	}
}

void heapify(vector<int>& nums, int idx, int n) {
	int left = (idx << 1) + 1, right = (idx << 1) + 2;
	int largest = idx;
	if (left < n && nums[left] > nums[largest]) largest = left;
	if (right < n && nums[right]>nums[largest]) largest = right;
	if (largest != idx) {
		swap(nums[largest], nums[idx]);
		heapify(nums, largest, n);
	}
}

void heapSort(vector<int>& nums) {
	int n = nums.size();
	// ����
	// �±�Ϊi�ĸ��ڵ��±�Ϊ(i-1)/2���±�Ϊn-1��Ϊn/2-1
	for (int i = n >> 1 - 1; i >= 0; --i) {
		heapify(nums, i, n);
	}
	// ����
	for (int i = n - 1; i > 0; --i) {
		// �����ĶѶ�Ԫ�ؽ�����δ���������ĩ��
		swap(nums[0], nums[i]);
		// ά���ӶѶ���δ��������ĩ�˵Ķѽṹ
		heapify(nums, 0, i);
	}
}

void countSort(vector<int>& nums) {
	int maxN = *max_element(nums.begin(), nums.end());
	// ��������
	vector<int>count(maxN+1);
	for (int& num : nums) ++count[num];
	// �ۼƼ���(������ǰֵ��Ӧ���±�)
	for (int i = 1; i <= maxN; ++i) count[i] += count[i - 1];

	int n = nums.size();
	vector<int>arr(n);
	// �����������ȶ�������ֵ������Ծ��ź���
	for (int i = n-1; i >= 0; --i) {
		// �ۼƼ�����1���Ƕ�Ӧ���±�����
		arr[count[nums[i]]-1] = nums[i];
		--count[nums[i]];
	}
	// ��ֵ��ԭ����
	nums.assign(arr.begin(), arr.end());
}

void bucketSort(vector<int>& nums) {
	int n = nums.size();
	// ����Ͱ����Ŀ
	int bucketNum = 5;
	// ����Ͱ�Ĵ�С
	int bucketSize = n / bucketNum;
	vector<vector<int>>buckets(bucketNum);
	// �������մ�Сװ����ӦͰ��
	for (const int& num : nums) {
		buckets[num / bucketSize].emplace_back(num);
	}
	// ÿ��Ͱʹ�ÿ���
	for (auto& bucket : buckets) {
		quickSort(bucket);
	}
	// д��ԭ����
	int i = -1;
	for (auto& bucket : buckets) {
		for (int& num : bucket) {
			nums[++i] = num;
		}
	}
}

void rdx_sort(vector<int>& nums, int n, int exp) {
	// 0-9ʮ��Ͱ
	vector<int>buckets(10);
	// ��ʱ����洢������
	vector<int>arr(n);
	int i;
	// Ͱ����(���˼��������˼�룬ʡȥ��ÿ��Ͱװ������ֵĿռ�)
	for (const int& num : nums) ++buckets[(num / exp) % 10];
	// �ۼƼ���
	for (i = 1; i < 10; ++i) buckets[i] += buckets[i - 1];
	// ע�⣺���ﵹ�������Ϊ���������ȶ��������������������֣�Ҳ���Ǻ��Ͱ�����֣��Ծ����ں��棬�Ƚ�Ͱ�������Ծ�����ǰ��
	// ���磺 10 12 15��ʮλ���Ŷ���Ͱ1���ۼƼ�����3������arr[3-1]Ӧ����15��������������arr[3-1]����10�������ȶ�
	for (i = n - 1; i >= 0; --i) {
		int idx = (nums[i] / exp) % 10;
		arr[buckets[idx] - 1] = nums[i];
		--buckets[idx];
	}
	nums.assign(arr.begin(), arr.end());
}
void radixSort(vector<int>& nums) {
	// �ҳ����ֵ�������û�������
	int maxN = *max_element(nums.begin(), nums.end());
	int n = nums.size();
	for (int i = 1; i <= maxN; i *= 10) {
		// �Դ�1-maxN��Ӧ�����Ļ������л�������
		rdx_sort(nums, n, i);
	}

}
//int main() {
//	srand((unsigned)time(NULL));
//	vector<int>nums(10);
//	for (int i = 0; i < 10; ++i) {
//		nums[i] = rand() % 100;
//	}
//	printArray(nums);
//	//bubbleSort(nums);
//	//selectSort(nums);
//	//mergeSort(nums);
//	//quickSort(nums);
//	//insertionSort(nums);
//	//shellSort(nums);
//	//heapSort(nums);
//	//countSort(nums);
//	//bucketSort(nums);
//	//radixSort(nums);
//	printArray(nums);
//	return 0;
//}