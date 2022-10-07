#include<iostream>
#include<string>
#include<vector>
using namespace std;

int getRes(vector<vector<int>>&arr, int n, int m) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		vector<int>row(m);
		for (int j = i; j < n; ++j) {
			int sum = 0;
			for (int k = 0; k < m; ++k) {
				row[k] += arr[j][k];
				if (arr[i][k] == 0 || arr[j][k] == 0) {
					sum = 0;
					continue;
				}
				
				sum += row[k];
				if (sum > res) {
					res = sum;
				}
			}
		}
	}
	return res;
}


//int main() {
//	int n = 4, m = 5;
//	vector<vector<int>>arr{ {1,0,0,0,0},{0,1,2,1,1},{0,1,1,1,1},{0,0,0,0,0} };
//	cout << getRes(arr, n, m) << endl;
//	return 0;
//}