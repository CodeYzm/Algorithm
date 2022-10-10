#include<iostream>
#include<string>
#include<queue>
#include<vector>
using namespace std;

int maxOrder(vector<vector<int>>&arr) {
	auto cmp = [](const vector<int>&p1, const vector<int>&p2) {
		return p1[1] < p2[1];
	};
	sort(arr.begin(), arr.end(), cmp);
	priority_queue<int,vector<int>,less<int>>q;
	int total = 0;
	for (vector<int>& pair : arr) {
		total += pair[0];
		q.emplace(pair[0]);
		if (total > pair[1]) {
			total -= q.top();
			q.pop();
		}
	}
	return q.size();
}
//int main() {
//	vector<vector<int>>arr{ {1,2},{2,13},{10,12},{20,30} };
//	cout << maxOrder(arr) << endl;
//	return 0;
//}