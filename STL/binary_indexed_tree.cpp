#include<iostream>
#include<vector>
using namespace std;

/*
	��״���飺ÿ���ڵ�Ľڵ�ֵ����������ӽڵ�ֵ֮��
	lowbit()ͨ��ȡ���һ��������λ����ϼӼ������������������������������и���Ԫ�أ������������ۼ�ǰ׺��
	���������ṹ�����Ը��ºͻ�ȡ������ʱ�临�Ӷ�ΪO(logn)
*/

class BIT {
private:
	int lowbit(const int& x) { // ��״����Ļ����������������Ϊ�����������Ĺ���
		return x & (-x);
	}
	vector<int>tree; //��״����
	int sizeT; // �����С
public:
	// ��Ϊlowbit(0)����0��û�����壬���tree[0]�ǲ��õ�
	// tree[0]�ǲ��õģ���tree[1]��ʼ�����tree(size+1)
	explicit BIT(int size):sizeT(size), tree(size+1) {} // explicit��ֹ�๹�캯������ʽ�Զ�ת��

	void update(int idx, int val) { // Ԫ�ظ��£�valΪԪ�ص����������ԭ����ֵΪ0����ֱ��������µ�Ԫ��ֵ
		while (idx <= sizeT) {
			tree[idx] += val; // �����Ĺ����и�������
			idx += lowbit(idx); // ����
		}
	}

	int query(int idx) { // ���ǰ׺��
		int prefix = 0;
		while (idx > 0) { // tree[0]�ǲ��õģ�
			prefix += tree[idx]; // �����Ĺ������ۼ�ǰ׺��
			idx -= lowbit(idx); // ����
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