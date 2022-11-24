#include<stdio.h>
//int add_int(int x) {
//	printf("add_int : %d\n", x);
//	return x + 1;
//}
//float add_float(float x) {
//	printf("add_float : %f\n", x);
//	return x + 0.1f;
//}
//int main(void) {
//	int x = 0;
//	_Generic(x, int : add_int(x), float:add_float(x));
//	_Generic(x+0.1f, int : add_int(x), float : add_float(x));
//	return 0;
//}

//int main(void)
//{
//	int a = 10;
//	int b = 0, c = 0;
//	_Generic(a + 0.1f, int:b, float : c, default:b)++;
//	printf("b=%d,c=%d\n", b, c);
//
//	_Generic(a += 1.1f, int:b, float : c, default:b)++;
//	printf("a=%d,b=%d,c=%d\n", a, b, c);
//}
