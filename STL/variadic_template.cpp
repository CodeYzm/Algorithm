#include<iostream>
using namespace std;

/*
   �ɱ����ģ�壺ʵ��ģ�庯����ģ����Ĳ�����Ŀ�ɱ�
*/
template<typename T, typename ...Args> //...����������
void print(T t, Args... rest) {
	cout << t << " ";
	cout << "�������в���������" << sizeof...(rest) << endl; //sizeof...������鿴�������м�������
}


//int main() {
//	print(1, 'a', "abc");
//	print(1, 2, "abc");
//	print(1, 2, "abc", 4);
//	return 0;
//}