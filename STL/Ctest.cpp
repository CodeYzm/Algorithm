#include<iostream>
#include <unordered_map>
#include <map>
#include<vector>
using namespace std;

void func() {
    return;
}

int func(int a) {
    return 0;
}
float funce(float x) {
    return x;
}
void func(int* a) {
    a = nullptr;
    //*a = 10;
    //*a = 10;
}

int main() {

    //int* a = new int(20);
    //func(a);
    //cout << *a << endl;
    //int a = 5;
    //a += (a++);
    //cout << a << endl;
    //int s[2] = { 0,1 };
    //int* p = s;
    //s += 1;
   // p += 1;
    int* a = nullptr;
    cout << sizeof(a) << endl;
    string s("hello");
    cout << s.size() << " " << sizeof(s) << endl;
    vector<int>arr;
    cout << arr.capacity() << sizeof(arr) << endl;
    return 0;
}


//unsigned int a = 2; int b = -3;
//cout << a + b << endl;
//int* a;
//cout << *a << endl;
//float(*pf)(float x);
//pf = funce;
//cout << pf(1.0) << endl;
//int* p[4];
//p[0] = new int(1);
//p[1] = new int(2);
//p[2] = new int(2);
//p[3] = new int(2);
//cout << *p[0] << endl;