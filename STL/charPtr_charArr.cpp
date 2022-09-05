#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;


struct ListNode{
    int val;
    ListNode* pre, * next;
    ListNode() :pre(nullptr), next(nullptr), val(0){}
};

class Solution{
public:
    ListNode* head, * tail;
    Solution(int w) {
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->pre = head;
        ListNode* tmp = head;
        for (int i = 0; i < w; ++i) {
            ListNode* newnode = new ListNode();
            tmp->next = newnode;
            newnode->pre = tmp;
            newnode->next = tail;
            tail->pre = newnode;
            tmp = tmp->next;
        }
    }

    string getRes(vector<int>&times) {
        string res;
        for (const int& t : times) {
            res += insert(t) + '0';
        }
        return res;
    }
    int insert(int t) {
        int idx = 1;
        ListNode* realhead = head->next;
        realhead->val += t;
        ListNode* cur = realhead->next;
        while (realhead->val > cur->val && cur != tail) {
            cur = cur->next;
            ++idx;
        }
        remove(realhead);
        realhead->next = cur;
        cur->pre->next = realhead;
        realhead->pre = cur->pre;
        cur->pre = realhead;
        return idx;
    }
    void remove(ListNode* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
};


//int main() {
//    char a[] = "hello";
//    char b[] = "hello";
//    const char* c = "hello";
//    const char* d = "hello";
//    cout << (a == b) << endl;
//    cout << (c == d) << endl;
//    cout << sizeof(a) << endl;
//    cout << sizeof(c) << endl;
//    cout << sizeof("hello") << endl;
//    int num1 = 3, num2 = 4;
//    cout << !!(num1 / num2 * 1.0) << endl;
//    return 0;
//}

