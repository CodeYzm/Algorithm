#include<iostream>
#include<cstdio>
using namespace std;

class W {
public:
    int b;
    int operator*(int a) {
        return  a + b;
    }
};

int main() {
    W w;
    w.b = 2;
    cout << w * 4 << endl;
    cout << 4 (::*) w << endl;
    cout << w.operator*(4) << endl;
    return 0;
}