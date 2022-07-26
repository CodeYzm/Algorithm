#include "sample_hashmap.h"
using namespace std;

template<typename T>
HashTable<T>::HashTable():buckets_size(init_buckets_size), keys_count(0), buckets(vector<Node<T>>(init_buckets_size)){}

template<typename T>
HashTable<T>::~HashTable() {
	clear();
}

template<typename T>
int HashTable<T>::hashfun(T val) {
	return val % buckets_size; // 取模是最简单的哈希函数，如果对于string等类型，需要模板偏特化来另外实现
}

template<typename T>
void HashTable<T>::insert(T val) {
	int key = hashfun(val);
	Node<T>* newNode = new Node<T>(key);
	newNode->next = buckets[key].next;
	buckets[key].next = newNode;
	++keys_count; // 元素数量增加
	expand(); // 考虑是否扩容
}

template<typename T>
void HashTable<T>::erase(T val) {
	int key = hashfun(val);
	Node<T>* cur = buckets[key].next; // 数组元素是结构体对象，.next调出结构体成员.
	Node<T>* pre = nullptr;
	while (cur) {
		if (cur->val == val) {
			if (pre == nullptr) { // 刚好在链表头部
				buckets[key].next = cur->next;
				delete cur;
			}
			else { // 不在链表头部
				pre->next = cur->next;
				delete cur;
			}
			return;
		}
		pre = cur;
		cur = cur->next;
	}
	--keys_count; // 元素数量减少
}

template<typename T>
bool HashTable<T>::find(T val) { // 计算key，并在对应链表中查找有无该数
	int key = hashfun(val);
	Node<T>* cur = buckets[key].next;
	while (cur) {
		if (cur->val == val) return true;
		cur = cur->next;
	}
	return false;
}

template<typename T>
void HashTable<T>::clear() {
	for (int i = 0; i < buckets_size; ++i) { // 遍历数组，每个散链表都用while循环删除申请的节点资源
		Node<T>* cur = buckets[i].next;
		while (cur) {
			Node<T>* pre = cur;
			cur = cur->next;
			delete pre;
		}
		buckets[i].next = nullptr;
	}
}

template<typename T>
void HashTable<T>::expand() { // 当key的数量比桶的数量多时扩容到原来的两倍
	if (keys_count > buckets_size) {
		buckets_size <<= 1;
		buckets.resize(buckets_size);
	}
}



template<typename T>
void HashTable<T>::print() {
	for (int i = 0; i < buckets_size; ++i) {
		Node<T>* cur = buckets[i].next;
		while (cur) {
			cout << cur->val << ' ';
			cur = cur->next;
		}
	}
	cout << endl;
}

//int main() {
//	HashTable<int>hash;
//	hash.insert(4);
//	hash.print();
//	hash.clear();
//	hash.print();
//	hash.insert(4);
//	hash.print();
//	hash.erase(4);
//	hash.print();
//	return 0;
//}