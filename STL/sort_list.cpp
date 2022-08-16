#include<iostream>
#include<list>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() :val(0), next(nullptr) {};
	ListNode(int _val) :val(_val), next(nullptr) {};
};

void print_list(ListNode* head) {
	ListNode* cur = head;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
}

// 冒泡排序
ListNode* bubble_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head;
	ListNode* tail = nullptr; // 维护遍历终点
	// 不断把大的值往右转移，遍历终点总是能变成最大值，再更新遍历终点
	while (tail != head) {
		ListNode* pre = dummy;
		ListNode* cur = pre->next;
		ListNode* nxt = cur->next;
		while (nxt != tail) {
			if (nxt->val < cur->val) { // 穿针引线交换节点
				pre->next = nxt;
				cur->next = nxt->next;
				nxt->next = cur;

			}
			else {
				cur = cur->next;
			}
			pre = pre->next;
			nxt = cur->next;
		}
		tail = cur;
	}
	head = dummy->next;
	dummy = nullptr;
	delete dummy;
	return head;
}

// 插入排序
ListNode* insert_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head; 
	ListNode* last_sorted = head; // 维护遍历起点
	ListNode* cur = head->next;
	while (cur) {
		// 如果排序起点<=当前节点值，说明位置正确，不用插入
		if (last_sorted->val <= cur->val) {
			last_sorted = last_sorted->next;
		}
		else {
			// 从开始往后遍历找到插入位置
			ListNode* pre = dummy;
			while (pre->next->val <= cur->val) pre = pre->next;
			last_sorted->next = cur->next;
			cur->next = pre->next;
			pre->next = cur;
		}
		cur = last_sorted->next;
	}
	head = dummy->next;
	dummy = nullptr;
	delete dummy;
	return head;
}

// 选择排序
ListNode* select_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head;
	ListNode* last_sorted = dummy; // 维护遍历起点
	while (last_sorted->next) {
		ListNode* pre = last_sorted;
		ListNode* cur = last_sorted->next;
		ListNode* min_cur = cur;
		ListNode* min_pre = pre;
		// 从遍历起点开始，寻找链表中的最小值
		while (cur) {
			if (cur->val < min_cur->val) {
				min_cur = cur;
				min_pre = pre;
			}
			cur = cur->next;
			pre = pre->next;
		}
		cur = last_sorted->next;
		pre = last_sorted;
		if (min_cur != cur) { // 如果存在比出发点小的最小节点
			if (min_pre == cur) { // 注意：可能会出现最小节点的前继节点刚好是cur节点的情况
				cur->next = min_cur->next;
				min_cur->next = cur;
				pre->next = min_cur;
			}
			else { 
				ListNode* nxt = cur->next;
				min_pre->next = cur;
				cur->next = min_cur->next;
				pre->next = min_cur;
				min_cur->next = nxt;
			}
		}
		last_sorted = last_sorted->next;
	}
	head = dummy->next;
	dummy = nullptr;
	delete dummy;
	return head;
}

// 归并排序
ListNode* mergeTowList(ListNode* L1, ListNode* L2) { // 合并两条有序链表
	if (!L1 || !L2) return L1 ? L1 : L2;
	if (L1->val < L2->val) {
		L1->next = mergeTowList(L1->next, L2);
		return L1;
	}
	else {
		L2->next = mergeTowList(L1, L2->next);
		return L2;
	}
}

ListNode* findMid(ListNode* head) { // 找到链表中间点
	if (!head || !head->next) return head;   // 这里head->next也要考虑
	ListNode* slow = head, * fast = head->next; // 0 1 2 3 得到 1
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

ListNode* merge_sort(ListNode* head) {
	if (!head || !head->next) return head; // 这里不要等到head == nullptr再返回，不然会栈溢出
	ListNode* mid = findMid(head);
	ListNode* nxt = mid->next; 
	mid->next = nullptr; // 将链表拆成两条，这里必须断开，不然findMid返回结果出错
	ListNode* left = merge_sort(head);
	ListNode* right = merge_sort(nxt);
	return mergeTowList(left, right); // 合并两条排序链表
}

// 快速排序
void q_sort(ListNode* head, ListNode* tail) {
	if (head == tail || head->next == tail) return; // head->next == tail直接返回(单个节点)
	ListNode* slow = head, *fast = head;
	int pivot = head->val;
	while (fast != tail) {
		if (fast->val < pivot) { // 如果快指针的值小于隔板值，慢指针往前一步，交换慢指针与快指针的值(因为此时慢指针肯定满足 >= pivot)
			slow = slow->next;
			int tmp = slow->val;
			slow->val = fast->val;
			fast->val = tmp;
		}
		fast = fast->next;
	}
	// 最后将隔板值换到中间，形成隔板左边都< pivot 隔板右边都 >= pivot
	head->val = slow->val;
	slow->val = pivot;
	q_sort(head, slow->next);
	q_sort(slow->next, tail);
}
ListNode* quick_sort(ListNode* head) {
	q_sort(head, nullptr);
	return head;
}

//int main() {
//	srand((unsigned)time(NULL));
//	ListNode* head = new ListNode(rand() % 20);
//	ListNode* cur = head;
//	for (int i = 0; i < 9; ++i) {
//		cur->next = new ListNode(rand() % 20);
//		cur = cur->next;
//	} 
//	print_list(head);
//	//head = insert_sort(head);
//	//head = bubble_sort(head);
//	//head = select_sort(head);
//	//head = merge_sort(head);
//	// head = quick_sort(head);
//	print_list(head);
//	while (head) {
//		ListNode* tmp = head->next;
//		delete head;
//		head = tmp;
//	}
//	return 0;
//}