#include<iostream>
#include<ctime>
#include<unordered_map>
using namespace std;

struct ListNode {
	ListNode* pre;
	ListNode* next;
	int val;
	int key;
	ListNode(int _key, int _val):key(_key),val(_val),pre(nullptr),next(nullptr) {};
};

class LRU {
private:
	const static int default_capacity = 50;
	ListNode* head, * tail;
	unordered_map<int, ListNode*>mp;
	int size;
	int capacity;
public:
	LRU():size(0), capacity(default_capacity) {
		head = new ListNode(0, 0);
		tail = new ListNode(0, 0);
		head->next = tail;
		tail->pre = head;
	}

	LRU(int _capacity) :size(0), capacity(_capacity) {
		head = new ListNode(0, 0);
		tail = new ListNode(0, 0);
		head->next = tail;
		tail->pre = head;
	}

	~LRU() {
		while (head) {
			ListNode* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	void put(int key, int value) { // 插入或者更新
		if (mp.find(key) != mp.end()) {
			ListNode* node = mp[key];
			node->val = value;
			move_to_head(node);
		}
		else {
			ListNode* newNode = new ListNode(key, value);
			mp[key] = newNode;
			add_to_head(newNode);
			++size; // 记得更新
			if (size > capacity) {
				ListNode* node = delete_tail();
				mp.erase(node->key); // 记得erase
				delete node;
				--size; // 记得更新
			}
		}
	}

	int get(int key) { // 获取数据
		if (mp.find(key) != mp.end()) {
			ListNode* node = mp[key];
			move_to_head(node);
			return node->val;
		}
		return -1;
	}

	void print() { // 为了测试，打印整个链表(不打印头尾节点)
		ListNode* cur = head->next;
		while (cur != tail) {
			cout << cur->val;
			cur = cur->next;
		}
		cout << endl;
	}
private:
	void add_to_head(ListNode* node) { // 向链表头部添加node
		head->next->pre = node;
		node->next = head->next;
		node->pre = head;
		head->next = node;
	}

	void move_to_head(ListNode* node) { // 将node移到链表头部
		remove(node);
		add_to_head(node);
	}

	void remove(ListNode* node) { // 移除node（注意：是从链表中移除，并没有删除节点）
		node->pre->next = node->next;
		node->next->pre = node->pre;
	}

	ListNode* delete_tail() { // 移除尾部节点(最近最少使用节点)，并返回该节点便于erase和delete操作
		ListNode* tmp = tail->pre;
		remove(tmp);
		return tmp;
	}
};

//int main() {
//	LRU lru(2);
//	lru.put(1, 1);
//	lru.print();
//	lru.put(4, 2);
//	lru.print();
//	cout << lru.get(4) << endl;
//	lru.put(4, 3);
//	lru.print();
//	return 0;
//}