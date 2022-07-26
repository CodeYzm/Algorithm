#include<iostream>
using namespace std;
struct ListNode {
	ListNode* next;
	int val;
	ListNode() :next(nullptr), val(0) {};
	ListNode(int _val) :next(nullptr), val(_val) {};
	ListNode(int _val, ListNode* nxt) :next(nxt), val(_val) {};
};

void print(ListNode* head) {
	ListNode* cur = head;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
}

ListNode* findMidnode3(ListNode* head) { // 靠后的版本：[1 2 3 4] -> 3
	ListNode* slow = head, * fast = head;
	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

ListNode* findMidnode2(ListNode* head) { // 靠前的版本：[1 2 3 4] -> 2
	ListNode* slow = head, * fast = head;
	while (fast->next != nullptr && fast->next->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

//int main() {
//	ListNode *head = new ListNode(1);
//	ListNode* cur = head;
//	for (int i = 2; i <= 4; ++i) {
//		cur->next = new ListNode(i);
//		cur = cur->next;
//	}
//	print(head);
//	ListNode* mid2 = findMidnode2(head);
//	ListNode* mid3 = findMidnode3(head);
//	cout << mid2->val << endl;
//	cout << mid3->val << endl;
//	return 0;
//}