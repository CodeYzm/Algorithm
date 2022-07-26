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
	return val % buckets_size; // ȡģ����򵥵Ĺ�ϣ�������������string�����ͣ���Ҫģ��ƫ�ػ�������ʵ��
}

template<typename T>
void HashTable<T>::insert(T val) {
	int key = hashfun(val);
	Node<T>* newNode = new Node<T>(key);
	newNode->next = buckets[key].next;
	buckets[key].next = newNode;
	++keys_count; // Ԫ����������
	expand(); // �����Ƿ�����
}

template<typename T>
void HashTable<T>::erase(T val) {
	int key = hashfun(val);
	Node<T>* cur = buckets[key].next; // ����Ԫ���ǽṹ�����.next�����ṹ���Ա.
	Node<T>* pre = nullptr;
	while (cur) {
		if (cur->val == val) {
			if (pre == nullptr) { // �պ�������ͷ��
				buckets[key].next = cur->next;
				delete cur;
			}
			else { // ��������ͷ��
				pre->next = cur->next;
				delete cur;
			}
			return;
		}
		pre = cur;
		cur = cur->next;
	}
	--keys_count; // Ԫ����������
}

template<typename T>
bool HashTable<T>::find(T val) { // ����key�����ڶ�Ӧ�����в������޸���
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
	for (int i = 0; i < buckets_size; ++i) { // �������飬ÿ��ɢ������whileѭ��ɾ������Ľڵ���Դ
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
void HashTable<T>::expand() { // ��key��������Ͱ��������ʱ���ݵ�ԭ��������
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