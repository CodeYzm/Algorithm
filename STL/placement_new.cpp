#include<iostream>
#include<vector>
using namespace std;


namespace jj {
	class Data {
	public:
		int num;
		Data() {}
		Data(int _num) : num(_num) {}
		~Data() {}
	};

}


//int main() {
//	cout << sizeof(jj::Data) << endl;
//	void* mem = malloc(sizeof(jj::Data));
//	jj::Data* data = new (mem) jj::Data(2);
//	cout << data->num << endl;
//	free(mem);
//	return 0;
//}