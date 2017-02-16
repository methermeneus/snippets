#include "snippets.h"

/********************************************************************
 **                                                                **
 **                    MATHEMATICAL FUNCTIONS                      **
 **                                                                **
 **                                                                **
 *******************************************************************/
int pow (int base, int exp) {
	int result = 1;
	while (exp) {
		if (exp & 1) result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

// Inline functions in header:
// sex()
// absval()
// floor()
// ceil()

/********************************************************************
 **                                                                **
 **                          UTILITIES                             **
 **                                                                **
 **                                                                **
 *******************************************************************/
void swap (int* x, int* y) {
	if (x == y) return; // x ^ x = 0, which would be bad!
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

void swapPtr (void** x, void** y) {
	if (x == y) return; // x ^ x = 0, which would be bad!
	// Each version basically evaluates to the other; I'm sure there'd be
	// no difference in a disassembler. Yes, I've tested that this works
	// withotu errors, at least in basic cases.
	//*x = (void*)((CONCAT(uint,WORDSIZE)) *x ^ (CONCAT(uint,WORDSIZE)) *y);
	//*y = (void*)((CONCAT(uint,WORDSIZE)) *y ^ (CONCAT(uint,WORDSIZE)) *x);
	//*x = (void*)((CONCAT(uint,WORDSIZE)) *x ^ (CONCAT(uint,WORDSIZE)) *y);
	*x = (void*) (((ptr) *x) ^ ((ptr) *y));
	*y = (void*) (((ptr) *y) ^ ((ptr) *x));
	*x = (void*) (((ptr) *x) ^ ((ptr) *y));
}

void printbits (uint8 input) {
	for (int i = 0; i < CHAR_BIT; ++i) {
		printf ("%u", input&(1<<(CHAR_BIT-1)) ? 1 : 0);
		input <<= 1;
	}
}
void printbits (int8 input) {
	printbits (*(uint8*)&input);
}
// Backwards, so it prints in the proper order.
void printbits (uint16 input) {
	printbits (*(((uint8*)&input)+1));
	printbits (*(uint8*)&input);
}
void printbits (int16 input) {
	printbits (*(uint16*)&input);
}
void printbits (uint32 input) {
	printbits (*(((uint16*)&input)+1));
	printbits (*(uint16*)&input);
}
void printbits (int32 input) {
	printbits (*(uint32*)&input);
}
void printbits (uint64 input) {
	printbits (*(((uint32*)&input)+1));
	printbits (*(uint32*)&input);
}
void printbits (int64 input) {
	printbits (*(uint64*)&input);
}
// easy to extend to 128 for a sytem that supports it.

//#define DEBUG
#ifdef DEBUG
/********************************************************************
 **                                                                **
 **                             MAIN                               **
 **                 FOR DEBUGGING PURPOSES ONLY                    **
 **                                                                **
 *******************************************************************/

int main () {

	int x[4] = {-1, 2, -3, 4};
	float y[4] = {-1.3, 2.718281828459045, -3.0, 4.17};

	for (int i = 0; i < 4; ++i) {
		printf ("x[%d] = %d;\ty[%d] = %f\n", i, abs(x[i]), i, abs(y[i]));
	}

	printf ("sizeof int is %lu\nsizeof float is %lu\n", sizeof (int), sizeof (float));

	return 0;
}
#endif
