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

// 冒泡排序
void bubbleSort(vector<int>&nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// 每次循环把最大的数换到n-i-1的位置
		for (int j = 1; j < n-i; ++j) {
			if (nums[j - 1] > nums[j]) swap(nums[j], nums[j - 1]);
		}
	}
}

// 选择排序
void selectSort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// 每次循环从i+1 - n里面挑一个最小的数换到i
		int minN = i;
		for (int j = i+1; j < n; ++j) {
			if (nums[j] < nums[minN]) minN = j;
		}
		swap(nums[minN], nums[i]);
	}
}

// 插入排序
void insertionSort(vector<int>& nums) {
	int n = nums.size();
	// 从第二个元素开始遍历
	for (int i = 1; i < n; ++i) {
		int num = nums[i];
		int j = i - 1;
		// 每一个比第i+1个元素大的元素都会被后移，最后小的元素会被插入到前面
		while (j >= 0 && nums[j] > num) {
			swap(nums[j], nums[j + 1]);
			--j;
		}
	}
}

// 希尔排序
void shellSort(vector<int>& nums) {
	int n = nums.size();
	// 取初始区间为n/2 ，每次区间都缩小1/2
	for (int gap = n >> 1; gap > 0; gap >>= 1) {
		// 以i = 1 * gap 开始， 往后遍历，不断进行插入排序
		for (int i = gap; i < n; ++i) {
			int num = nums[i];
			// 插入排序部分，如果上一个元素比当前元素小，则将上一个元素移到前面，找到合适的插入位置
			for (int j = i - gap; j >= 0 && nums[j] > num; j -= gap) {
				swap(nums[j], nums[j + gap]);
			}
		}
	}
}

// 归并排序
void merge(vector<int>& nums, vector<int>& arr, int left, int mid, int right) {
	int i = left, j = mid + 1;
	int start = left - 1;
	while (i <= mid && j <= right) {
		arr[++start] = nums[i] < nums[j] ? nums[i++] : nums[j++];
	}
	// 合并剩余元素
	while (i <= mid) arr[++start] = nums[i++];
	while (j <= right) arr[++start] = nums[j++];
	// 赋值给原数组
	while (left <= right) {
		nums[left] = arr[left];
		++left;
	}
}
void m_sort(vector<int>& nums, vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) >> 1;
		// 递归分组
		m_sort(nums, arr, left, mid);
		m_sort(nums, arr, mid + 1, right);
		// 最后一层递归合并
		merge(nums, arr, left, mid, right);
	}
}
void mergeSort(vector<int>& nums) {
	int n = nums.size();
	vector<int>arr(n);
	m_sort(nums, arr, 0, n - 1);
}

// 快速排序
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

// 堆排序
void heapify(vector<int>& nums, int idx, int n) {
	// 左右孩子的下标
	int left = (idx << 1) + 1, right = (idx << 1) + 2;
	int largestIdx = idx;
	// 升序排序用大顶堆，因为每次能将数组首部(堆顶)最大的元素换到数组末端
	// 左右孩子下标可能越界
	if (left < n && nums[left] > nums[largestIdx]) largestIdx = left;
	if (right < n && nums[right] > nums[largestIdx]) largestIdx = right;
	// 如果左右孩子有大于父亲的数，交换位置，并继续往后维护堆结构
	if (largestIdx != idx) {
		swap(nums[largestIdx], nums[idx]);
		heapify(nums, largestIdx, n);
	}
}


void heapSort(vector<int>& nums) {
	int n = nums.size();
	// 建堆
	// 下标为i的父节点下标为(i-1)/2，下标为n-1则为n/2-1
	for (int i = n >> 1 - 1; i >= 0; --i) {
		heapify(nums, i, n);
	}
	// 排序
	for (int i = n - 1; i > 0; --i) {
		// 将最大的堆顶元素交换到未排序数组的末端
		swap(nums[0], nums[i]);
		// 维护从堆顶到未排序数组末端的堆结构
		heapify(nums, 0, i);
	}
}

// 计数排序
void countSort(vector<int>& nums) {
	int n = nums.size();
	int maxN = *max_element(nums.begin(), nums.end());
	vector<int>count(maxN+1);
	for (const int& num : nums)++count[num];
	for (int i = 1; i <= maxN; ++i) count[i] += count[i - 1];
	vector<int>arr(n); // 临时数组，存储排序后的数值
	for (int i = n - 1; i >= 0; --i) { // 倒序遍历可以让排序稳定，原来在后面的数仍旧在后面，因为count数组是累加的
		int num = nums[i];
		arr[count[num] - 1] = num;
		--count[num];
	}
	nums.assign(arr.begin(), arr.end());
}


// 桶排序
void bucketSort(vector<int>& nums) {
	int n = nums.size();
	// 根据值域区间设置桶的数目和大小
	int bucketNum = 10, bucketSize = 10;
	vector<vector<int>>buckets(bucketNum);
	// 将数按照大小装进对应桶里
	for (const int& num : nums) {
		buckets[num / bucketSize].emplace_back(num);
	}
	// 每个桶使用快排
	for (auto& bucket : buckets) {
		quickSort(bucket);
	}
	// 写回原数组
	int i = -1;
	for (auto& bucket : buckets) {
		for (int& num : bucket) {
			nums[++i] = num;
		}
	}
}

// 基数排序
void rdx_sort(vector<int>& nums, int exp) {
	int n = nums.size();
	vector<int>arr(n);
	// 0-9十个桶
	vector<int>bucket(10);
	// 每一位都采用桶排序的思想装入桶中
	for (const int& num : nums) {
		++bucket[(num / exp) % 10];
	}
	// 采用计数排序的思想合并序列
	for (int i = 1; i < 10; ++i) bucket[i] += bucket[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		int num = (nums[i] / exp) % 10;
		arr[bucket[num]-1] = nums[i];
		--bucket[num];
	}
	nums.assign(arr.begin(), arr.end());
}

void radixSort(vector<int>& nums) {
	int maxN = *max_element(nums.begin(), nums.end());
	// 对每一位进行非比较的桶排序
	for (int i = 1; i <= maxN; i *= 10) {
		rdx_sort(nums, i);
	}
}


int main() {
	srand((unsigned)time(NULL));
	vector<int>nums(10);
	for (int i = 0; i < 10; ++i) {
		nums[i] = rand() % 100;
	}
	printArray(nums);
	//bubbleSort(nums);
	//selectSort(nums);
	//mergeSort(nums);
	//quickSort(nums);
	//insertionSort(nums);
	//shellSort(nums);
	//heapSort(nums);
	//countSort(nums);
	//bucketSort(nums);
	//radixSort(nums);
	printArray(nums);
	return 0;
}
