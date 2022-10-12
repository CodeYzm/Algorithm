#include<iostream>
#include<stdio.h>
#include<functional>
#include<vector>
#include<queue>
using namespace std;

class Solution {
private:
    struct TreeNode {
        TreeNode* left, * right;
        int val, lazy;
        TreeNode() :left(nullptr), right(nullptr), val(0), lazy(0) {}
        TreeNode(int _val, int _lazy) :left(nullptr), right(nullptr), val(_val), lazy(_lazy) {}
    };
    TreeNode* root;
    TreeNode* buildTree(int curLeft, int curRight) {
        if (curLeft > curRight) return nullptr;
        else if (curLeft == curRight) {
            TreeNode* node = new TreeNode();
            return node;
        }
        else {
            int mid = curLeft + ((curRight - curLeft) >> 1);
            TreeNode* node = new TreeNode();
            node->left = buildTree(curLeft, mid);
            node->right = buildTree(mid + 1, curRight);
            return node;
        }
    }

    void pushUp(TreeNode* node) {
        node->val = node->left->val + node->right->val;
    }
    void pushDown(TreeNode* node, int leftChild, int rightChild) {
        if (node->lazy == 0) return;

        node->left->lazy += node->lazy;
        node->left->val += leftChild * node->lazy;

        node->right->lazy += node->lazy;
        node->right->val += rightChild * node->lazy;

        node->lazy = 0;
    }
    void update(TreeNode* node, int curLeft, int curRight, int updateLeft, int updateRight, int val) {
        if (curLeft == updateLeft && curRight == updateRight) {
            node->lazy += val;
            node->val += (curRight - curLeft + 1) * val;
            return;
        }
        int mid = curLeft + ((curRight - curLeft) >> 1);
        if (mid < updateLeft) update(node->right, mid + 1, curRight, updateLeft, updateRight, val);
        else if (mid >= updateRight) update(node->left, curLeft, mid, updateLeft, updateRight, val);
        else {
            update(node->left, curLeft, mid, updateLeft, mid, val);
            update(node->right, mid + 1, curRight, mid + 1, updateRight, val);
        }
        pushUp(node);
    }
    int query(TreeNode* node, int curLeft, int curRight, int queryLeft, int queryRight) {
        if (curLeft == queryLeft && curRight == queryRight) {
            return node->val;
        }
        int mid = curLeft + ((curRight - curLeft) >> 1);
        pushDown(node, mid - curLeft + 1, curRight - mid);
        if (mid < queryLeft) return query(node->right, mid + 1, curRight, queryLeft, queryRight);
        else if (mid >= queryRight) return query(node->left, curLeft, mid, queryLeft, queryRight);
        else return query(node->left, curLeft, mid, queryLeft, mid) +
            query(node->right, mid + 1, curRight, mid + 1, queryRight);
    }
public:
    void init(int n) {
        root = buildTree(1, n);
    }
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        init(n);
        for (vector<int>& booking : bookings) {
            update(root, 1, n, booking[0], booking[1], booking[2]);

        }
        vector<int>res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = query(root, 1, n, i + 1, i + 1);
        }
        print_tree();
        print_lazy();
        return res;
    }
    void print_tree() {
        if (root == nullptr) {
            cout << "null" << endl;
            return;
        }
        TreeNode* tmp = nullptr;
        queue<TreeNode*>q;
        q.emplace(root);
        while (!q.empty()) {
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                tmp = q.front();
                if (tmp == nullptr) cout << "null" << " ";
                else {
                    cout << tmp->val << " ";
                    q.emplace(tmp->left);
                    q.emplace(tmp->right);
                }
                q.pop();
            }
            cout << endl;
        }

    }
    void print_lazy() {
        if (root == nullptr) {
            cout << "null" << endl;
            return;
        }
        TreeNode* tmp = nullptr;
        queue<TreeNode*>q;
        q.emplace(root);
        while (!q.empty()) {
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                tmp = q.front();
                if (tmp == nullptr) cout << "null" << " ";
                else {
                    cout << tmp->lazy << " ";
                    q.emplace(tmp->left);
                    q.emplace(tmp->right);
                }
                q.pop();
            }
            cout << endl;
        }

    }
};

//int main() {
//  Solution s;
//  vector<vector<int>>arr = { {3,3,5 }, { 1,3,20 }, { 1,2,15 }};
//  s.corpFlightBookings(arr, 3);
//	return 0;
//}