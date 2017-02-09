#include <cstdio>


void printbits (unsigned int num) {
	unsigned int size = sizeof (unsigned int);
	unsigned int maxPow = 1<<(size*8-1);
	for (int i = 0; i < size * 8; ++i) {
		//for (int j=0; j<8; ++j) {
		printf ("%u", num&maxPow ? 1 : 0);
		num <<= 1;
	}
}
/* */
inline float abs (float x) {
	int y = ((int&)x & 0x7fffffff);
	return (float&) y;
}

int main (int argc, char** argv, char** env) {
	return 0;
}
