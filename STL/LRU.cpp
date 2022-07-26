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

	void put(int key, int value) { // ������߸���
		if (mp.find(key) != mp.end()) {
			ListNode* node = mp[key];
			node->val = value;
			move_to_head(node);
		}
		else {
			ListNode* newNode = new ListNode(key, value);
			mp[key] = newNode;
			add_to_head(newNode);
			++size; // �ǵø���
			if (size > capacity) {
				ListNode* node = delete_tail();
				mp.erase(node->key); // �ǵ�erase
				delete node;
				--size; // �ǵø���
			}
		}
	}

	int get(int key) { // ��ȡ����
		if (mp.find(key) != mp.end()) {
			ListNode* node = mp[key];
			move_to_head(node);
			return node->val;
		}
		return -1;
	}

	void print() { // Ϊ�˲��ԣ���ӡ��������(����ӡͷβ�ڵ�)
		ListNode* cur = head->next;
		while (cur != tail) {
			cout << cur->val;
			cur = cur->next;
		}
		cout << endl;
	}
private:
	void add_to_head(ListNode* node) { // ������ͷ�����node
		head->next->pre = node;
		node->next = head->next;
		node->pre = head;
		head->next = node;
	}

	void move_to_head(ListNode* node) { // ��node�Ƶ�����ͷ��
		remove(node);
		add_to_head(node);
	}

	void remove(ListNode* node) { // �Ƴ�node��ע�⣺�Ǵ��������Ƴ�����û��ɾ���ڵ㣩
		node->pre->next = node->next;
		node->next->pre = node->pre;
	}

	ListNode* delete_tail() { // �Ƴ�β���ڵ�(�������ʹ�ýڵ�)�������ظýڵ����erase��delete����
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