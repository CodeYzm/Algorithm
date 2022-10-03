#pragma once
#include<vector>
#include<iostream>
#include<queue>
using namespace std;

// 树节点
struct TreeNode {
	int val;
	TreeNode* left, * right;
	TreeNode(int _val) :val(_val), left(nullptr), right(nullptr) {}
};

// 打印数组
template<class T>
void print_vector(const vector<T>&arr){
	for (const T& ele : arr) {
		cout << ele << " ";
	}
	cout << endl;
}

// 层序遍历打印树
void print_tree(TreeNode* root) {
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