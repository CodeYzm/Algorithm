#include<iostream>
#include<stdio.h>
#include<stack>
using namespace std;

double getNum(string s) {
	int n = s.size();
	int i = 0;
	double dWeight = 10;
	bool flag = true;
	double intNum = 0.0, doubleNUm = 0.0;
	double res = 0.0;
	while (i < n) {
		if (s[i] == '.') {
			flag = false;
		}
		else if (isdigit(s[i])) {
			if (flag) {
				intNum *= 10;
				intNum += ((double)s[i] - '0');
			}
			else {
				doubleNUm += ((double)s[i] - '0') / dWeight;
				dWeight *= 10;
			}

		}
		else {
			if (s[i] == '+') {
				res += intNum + doubleNUm;
			}
			else {
				res -= intNum + doubleNUm;
			}
			flag = true;
			dWeight = 10;
			intNum = 0.0; doubleNUm = 0.0;
		}
		++i;
	}
	return res;
}
int getString(string& s, int idx) {
	while (idx < s.size()) {
		if (isdigit(s[idx]) || s[idx] == '.')++idx;
		else break;
	}
	return idx;
}
double getRes(string&s) {
	int n = s.size();
	int i = 0;
	double res = 0.0;
	while (i < n) {
		if (s[i] == '+' || s[i] == '-') {
			++i;
			int right = getString(s, i);
			double tmp = getNum(s.substr(i, right - i + 1));
			if (s[i] == '+') res += tmp;
			else res -= tmp;
			i = right + 1;
		}
		else {
			int right = getString(s, i);
			double tmp = getNum(s.substr(i, right - i + 1));
			res = tmp;
			i = right + 1;
		}

	}
	return res;
}
int main() {
	string s = "1.25+1.3";
	cout << getRes(s) << endl;
	return 0;
}