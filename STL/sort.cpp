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
		// 每次循环把最大的数换到n-i-1的位置
		for (int j = 1; j < n-i; ++j) {
			if (nums[j - 1] > nums[j]) swap(nums[j], nums[j - 1]);
		}
	}
}

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

void merge(vector<int>& nums, vector<int>& arr, int left, int mid, int right) {
	int i = left, j = mid + 1;
	int start = left-1;
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

void shellSort(vector<int>& nums) {
	int n = nums.size();
	// 取初始增量为n/2 ，每次增量都缩小1/2
	for (int inc = n >> 1; inc > 0; inc >>= 1) {
		// inc为插入排序的遍历起点，因为默认第一个元素是有序的
		for (int i = inc; i < n; ++i) {
			int num = nums[i];
			// 如果上一个元素比当前元素大，不断后移
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

void countSort(vector<int>& nums) {
	int maxN = *max_element(nums.begin(), nums.end());
	// 计数数组
	vector<int>count(maxN+1);
	for (int& num : nums) ++count[num];
	// 累计计数(用于求当前值对应的下标)
	for (int i = 1; i <= maxN; ++i) count[i] += count[i - 1];

	int n = nums.size();
	vector<int>arr(n);
	// 倒序让排序稳定，后出现的数字仍旧排后面
	for (int i = n-1; i >= 0; --i) {
		// 累计计数减1就是对应的下标索引
		arr[count[nums[i]]-1] = nums[i];
		--count[nums[i]];
	}
	// 赋值给原数组
	nums.assign(arr.begin(), arr.end());
}

void bucketSort(vector<int>& nums) {
	int n = nums.size();
	// 设置桶的数目
	int bucketNum = 5;
	// 计算桶的大小
	int bucketSize = n / bucketNum;
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

void rdx_sort(vector<int>& nums, int n, int exp) {
	// 0-9十个桶
	vector<int>buckets(10);
	// 临时数组存储排序结果
	vector<int>arr(n);
	int i;
	// 桶计数(用了计数排序的思想，省去了每个桶装多个数字的空间)
	for (const int& num : nums) ++buckets[(num / exp) % 10];
	// 累计计数
	for (i = 1; i < 10; ++i) buckets[i] += buckets[i - 1];
	// 注意：这里倒序遍历是为了让排序稳定，让排在数组后面的数字，也就是后进桶的数字，仍旧排在后面，先进桶的数字仍旧排在前面
	// 比如： 10 12 15按十位数排都在桶1，累计计数是3，所以arr[3-1]应该是15，如果正序遍历，arr[3-1]就是10，排序不稳定
	for (i = n - 1; i >= 0; --i) {
		int idx = (nums[i] / exp) % 10;
		arr[buckets[idx] - 1] = nums[i];
		--buckets[idx];
	}
	nums.assign(arr.begin(), arr.end());
}
void radixSort(vector<int>& nums) {
	// 找出最大值用于设置基数上限
	int maxN = *max_element(nums.begin(), nums.end());
	int n = nums.size();
	for (int i = 1; i <= maxN; i *= 10) {
		// 对从1-maxN对应量级的基数进行基数排序
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