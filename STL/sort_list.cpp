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

// ð������
ListNode* bubble_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head;
	ListNode* tail = nullptr; // ά�������յ�
	// ���ϰѴ��ֵ����ת�ƣ������յ������ܱ�����ֵ���ٸ��±����յ�
	while (tail != head) {
		ListNode* pre = dummy;
		ListNode* cur = pre->next;
		ListNode* nxt = cur->next;
		while (nxt != tail) {
			if (nxt->val < cur->val) { // �������߽����ڵ�
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

// ��������
ListNode* insert_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head; 
	ListNode* last_sorted = head; // ά���������
	ListNode* cur = head->next;
	while (cur) {
		// ����������<=��ǰ�ڵ�ֵ��˵��λ����ȷ�����ò���
		if (last_sorted->val <= cur->val) {
			last_sorted = last_sorted->next;
		}
		else {
			// �ӿ�ʼ��������ҵ�����λ��
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

// ѡ������
ListNode* select_sort(ListNode* head) {
	ListNode* dummy = new ListNode();
	dummy->next = head;
	ListNode* last_sorted = dummy; // ά���������
	while (last_sorted->next) {
		ListNode* pre = last_sorted;
		ListNode* cur = last_sorted->next;
		ListNode* min_cur = cur;
		ListNode* min_pre = pre;
		// �ӱ�����㿪ʼ��Ѱ�������е���Сֵ
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
		if (min_cur != cur) { // ������ڱȳ�����С����С�ڵ�
			if (min_pre == cur) { // ע�⣺���ܻ������С�ڵ��ǰ�̽ڵ�պ���cur�ڵ�����
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

// �鲢����
ListNode* mergeTowList(ListNode* L1, ListNode* L2) { // �ϲ�������������
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

ListNode* findMid(ListNode* head) { // �ҵ������м��
	if (!head || !head->next) return head;   // ����head->nextҲҪ����
	ListNode* slow = head, * fast = head->next; // 0 1 2 3 �õ� 1
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

ListNode* merge_sort(ListNode* head) {
	if (!head || !head->next) return head; // ���ﲻҪ�ȵ�head == nullptr�ٷ��أ���Ȼ��ջ���
	ListNode* mid = findMid(head);
	ListNode* nxt = mid->next; 
	mid->next = nullptr; // ���������������������Ͽ�����ȻfindMid���ؽ������
	ListNode* left = merge_sort(head);
	ListNode* right = merge_sort(nxt);
	return mergeTowList(left, right); // �ϲ�������������
}

// ��������
void q_sort(ListNode* head, ListNode* tail) {
	if (head == tail || head->next == tail) return; // head->next == tailֱ�ӷ���(�����ڵ�)
	ListNode* slow = head, *fast = head;
	int pivot = head->val;
	while (fast != tail) {
		if (fast->val < pivot) { // �����ָ���ֵС�ڸ���ֵ����ָ����ǰһ����������ָ�����ָ���ֵ(��Ϊ��ʱ��ָ��϶����� >= pivot)
			slow = slow->next;
			int tmp = slow->val;
			slow->val = fast->val;
			fast->val = tmp;
		}
		fast = fast->next;
	}
	// ��󽫸���ֵ�����м䣬�γɸ�����߶�< pivot �����ұ߶� >= pivot
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