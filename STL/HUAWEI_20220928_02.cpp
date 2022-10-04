#include<iostream>
#include<string>
#include<vector>
using namespace std;

//int getRes(vector<vector<int>>&arr, int n, int m) {
//	vector<int>dp(m);
//	int res = 0;
//	for (int i = 0; i < n; ++i) {
//		for (int& num : dp) num = 0;
//		for (int j = i; j < n; ++j) {
//			int sum = 0;
//			for (int k = 0; k < m; ++k) {
//				dp[k] += arr[j][k];
//				sum += dp[k];
//				if (sum > res) {
//					res = sum;
//				}
//			}
//		}
//	}
//	return res;
//}

int max
int getRes(vector<vector<int>>& arr, int n, int m) {
	int res = 0;
	vector<vector<int>>heights(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i == 0) heights[i][j] = arr[i][j] == 0 ? 0 : 1;
			else heights[i][j] = arr[i][j] == 0 ? 0 : (heights[i - 1][j] + 1);
		}

	}
	return res;
}

int main() {
	int n = 4, m = 5;
	vector<vector<int>>arr{ {1,0,0,0,0},{0,1,2,1,1},{0,1,1,1,1},{0,0,0,0,0} };
	// cout << getRes(arr, n, m) << endl;
	return 0;
}