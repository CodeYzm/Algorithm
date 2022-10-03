#include<iostream>
#include "yzm_box.h"
#include<string>
#include<vector>
using namespace std;

// �ַ���str��ch�ָ���Ҵ洢��arr
void split(vector<int>&arr, string str, char ch) {
	string tmp;
	for (const char& ch : str) {
		if (isdigit(ch)) tmp += ch;
		else {
			arr.emplace_back(stoi(tmp));
			tmp = "";
		}
	}
	arr.emplace_back(stoi(tmp));
	//print_vector<int>(arr);
}

// ���齨��
TreeNode* buildTree(vector<int>& arr, int idx) {
	if (idx >= arr.size() || arr[idx] == 0) return nullptr;
	TreeNode* node = new TreeNode(arr[idx]);
	node->left = buildTree(arr, idx * 2 + 1);
	node->right = buildTree(arr, idx * 2 + 2);
	return node;
}

// ����·���ҵ��ڵ�
TreeNode* findStart(vector<int>&path, TreeNode*root, int idx) {
	if (path[idx] != root->val) return nullptr;
	if (idx == path.size() - 1) return root;
	TreeNode* leftf = nullptr, * rightf = nullptr;
	if (root->left) {
		leftf = findStart(path, root->left, idx + 1);
	}
	if (root->right) {
		rightf = findStart(path, root->right, idx + 1);
	}
	return leftf == nullptr ? rightf : leftf;
}

// ����㿪ʼ�������滻����
void replace(TreeNode* root1, TreeNode* root2) {
	root1->val = root2->val;
	if (root1->left == nullptr) { // ����Ϊ�գ�ֱ��ָ������
		root1->left = root2->left;
	}
	else if (root2->left != nullptr) { // ����Ϊ��������Ҳ��Ϊ�գ���ݹ��滻
		replace(root1->left, root2->left);
	} // ����Ϊ�գ�����Ϊ�գ���ɶҲ������

	// ����ͬ��
	if (root1->right == nullptr) {
		root1->right = root2->right;
	}
	else if (root2->right != nullptr) {
		replace(root1->right, root2->right);
	} 
}

//int main() {
//	string str;
//
//	//getline(cin, str);
//	str = "[1,1,2,0,0,4,5]";
//	vector<int>father;
//	split(father, str.substr(1, str.size() - 2), ',');
//	TreeNode* root1 = buildTree(father, 0);
//
//	//print_tree(root1);
//	//getline(cin, str);
//	str = "/1/2";
//	vector<int>path;
//	split(path, str.substr(1, str.size() - 1), '/');
//	TreeNode* start = findStart(path, root1, 0);
//	//cout << start->val << endl;
//
//	//getline(cin, str);
//	str = "[5,3,0]";
//	vector<int>son;
//	split(son, str.substr(1, str.size() - 2), ',');
//	TreeNode* root2 = buildTree(son, 0);
//	//print_tree(root2);
//
//	replace(start, root2);
//	print_tree(root1);
//	return 0;
//}