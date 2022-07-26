#include<iostream>
#include<ctime>
#include <windows.h> // Linux��#include <unistd.h>������ʹ��sleep()����
#include<winbase.h>
#include<unordered_map>
using namespace std;

constexpr int default_capacity = 50, ttl = 1; // Ĭ�ϻ���������Ĭ�ϻ�������ʱ��

struct ListNode {
	ListNode* pre;
	ListNode* next;
	int val;
	int key;
	time_t expiretime;
	ListNode(int _key, int _val) :key(_key), val(_val), expiretime(time(nullptr)), pre(nullptr), next(nullptr) {};
};

class LRU {
private:
	ListNode* head, * tail;
	unordered_map<int, ListNode*>mp;
	int size;
	int capacity;
public:
	LRU() :size(0), capacity(default_capacity) {
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
		time_t curtime = time(nullptr); // ��һ�����Ҫ�̰߳�ȫ�Ļ����԰������curtimeȫ������time(nullptr)����ִֹ�е������߳��л������»�������ʱ���Ѿ���ʱ
		if (mp.find(key) != mp.end()) {
			ListNode* node = mp[key];
			node->val = value;
			node->expiretime = curtime + ttl;
			move_to_head(node);
		}
		else {
			ListNode* newNode = new ListNode(key, value);
			newNode->expiretime = curtime + ttl;
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
			time_t curtime = time(nullptr);
			if (difftime(node->expiretime, curtime) <= 0) { // ��ǰϵͳʱ���Ƿ񳬹���Ԥ���ʱ��
				remove(node);
				mp.erase(key);
				--size;
				delete node;
				return -1;
			}
			move_to_head(node);
			node->expiretime = curtime + ttl; // ʹ���˸����ݣ����Ը���Ԥ��ʱ��
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
//	Sleep(1000); // 1000ms
//	cout << lru.get(4) << endl;
//	lru.put(4, 3);
//	lru.print();
//	return 0;
//}