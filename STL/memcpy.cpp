#include<iostream>
using namespace std;

void* Memcpy(const void* src, void* dst, size_t len) {
	char* src1, * dst1;
	if (src < dst && (char*)src + len > dst) {
		src1 = (char*)src + len - 1; dst1 = (char*)dst + len - 1;
		while (len--) {
			*dst1-- = *src1--;
		}
	}
	else {
		src1 = (char*)src; dst1 = (char*)dst;
		while (len--) {
			*dst1++ = *src1++;
		}
	}
	return dst;
}

//int main() {
//	char buf[1024] = "abcdefg";
//	//Memcpy(buf, buf+2, 20);
//	memcpy(buf, buf + 2, 20);
//	printf("%s\n", buf);
//	return 0;
//}