#include<iostream>
#include<vector>
using namespace std;

/*
	树状数组：每个节点的节点值是所管理的子节点值之和
	lowbit()通过取最后一个二进制位，配合加减操作进行爬树和下树，爬树过程中更新元素，下树过程中累计前缀和
	由于是树结构，所以更新和获取操作的时间复杂度为O(logn)
*/

class BIT {
private:
	int lowbit(const int& x) { // 树状数组的基本操作，可以理解为爬树和下树的过程
		return x & (-x);
	}
	vector<int>tree; //树状数组
	int sizeT; // 数组大小
public:
	// 因为lowbit(0)还是0，没有意义，因此tree[0]是不用的
	// tree[0]是不用的，从tree[1]开始，因此tree(size+1)
	explicit BIT(int size):sizeT(size), tree(size+1) {} // explicit防止类构造函数的隐式自动转换

	void update(int idx, int val) { // 元素更新，val为元素的增量，如果原数组值为0，则直接输入更新的元素值
		while (idx <= sizeT) {
			tree[idx] += val; // 爬树的过程中更新增量
			idx += lowbit(idx); // 爬树
		}
	}

	int query(int idx) { // 获得前缀和
		int prefix = 0;
		while (idx > 0) { // tree[0]是不用的！
			prefix += tree[idx]; // 下树的过程中累计前缀和
			idx -= lowbit(idx); // 下树
		}
		return prefix;
	}

	void print(vector<int>& arr) {
		for (const int& num : arr) cout << num << ' ';
		cout << endl;
	}
};

//int main() {
//	vector<int>arr(10);
//	BIT bit(10);
//	for (int i = 0; i < 10; ++i) {
//		arr[i] = rand() % 20;
//		bit.update(i+1, arr[i]);
//	}
//	bit.print(arr);
//	for (int i = 0; i < 10; ++i) {
//		cout << bit.query(i+1) << ' ';
//	}
//	cout << endl;
//	return 0;
//}