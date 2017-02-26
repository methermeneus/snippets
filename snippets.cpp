#ifndef RAG_SNIPPETS
/********************************************************************
 **                        CODE SNIPPETS                           **
 ** by Randy Grant (methermeneus@gmail.com)                        **
 **                                                                **
 **     Code snippets for general use, by Randy, often with        **
 ** (extensive) assistance from the internet. A few of these are   **
 ** implemented in the C standard library, but I wanted my own     **
 ** versions for various reasons: math functions that work with    **
 ** int, no branching, etc.                                        **
 **                                                                **
 **     Basically, yes, I realize most of these are either         **
 ** implemented better elsewhere or unnecessary, but this is the   **
 ** kind of thing I do for fun, okay?                              **
 **                                                                **
 ** TODO: - overload for all integer types                         **
 **       - printf overloading for common arrays                   **
 **       - overload arrays to structs with length and maybe some  **
 **           methods WITHOUT templates, because screw C++         **
 **           templates. Or I can just wait 'til Jonathan Blow     **
 **           releases JAI, I suppose.                             **
 **       - Make a Vim shortcut to create these comment boxes, so  **
 **           I can get rid of the copy/paste example on the bottom**
 **           of the file.                                         **
 **       - Error reporting function (no, we don't need try/throw/ **
 **           catch, dammit!). Something along the lines of        **
 **           int error (char* mesg, int retval), maybe.           **
 **                                                                **
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#if defined (__unix__) || defined (__linux__) || (defined (__APPLE__) && defined (__MACH__)) || defined (__FreeBSD__) // posix check
// POSIX ONLY!!!!
#include <termios.h>
#endif

/********************************************************************
 **                                                                **
 **                            MACROS                              **
 **                                                                **
 *******************************************************************/

// Quick concatenation thing, because I actually like doing this
// sometimes. All caps because MACROS. To concatenate 3 items, CONCAT(a,
// (CONCAT (b, c)) (or CONCAT (CONCAT (a, b), c), whatever works best in
// the situation). See isocpp.org/wiki/faq for the reason for the
// indirection layer. NEVER USE CONCAT_HIDDEN DIRECTLY!
//
// Useful for, say, 
//	CONCAT(uint, WORDSIZE) function (CONCAT(int, WORDSIZE);
//	which would expand to:
//	uint64 function (int64);
//	on a 64-bit system or
//	uint32 function (int32);
//	on a 32-bit system.
//
#define CONCAT(a,b) CONCAT_HIDDEN(a,b)
#define CONCAT_HIDDEN(a,b) a ## b


/********************************************************************
 **                                                                **
 **                        USEFUL NUMBERS                          **
 **                                                                **
 *******************************************************************/
// We don't need to #define BITS 8 because limits.h defines CHAR_BIT as
// 8

// Integral types
typedef int8_t       int8;
typedef int16_t      int16;
typedef int32_t      int32;
typedef int64_t      int64;
typedef uint8_t      uint8;
typedef uint16_t     uint16;
typedef uint32_t     uint32;
typedef uint64_t     uint64;
typedef unsigned int uint;
typedef uintptr_t    ptr;

// Byte stuff
#define PTR_WIDTH sizeof(uintptr_t)*CHAR_BIT

// Remember, definitions have changed. Now 1 kilobyte (Kb) is 1000 bytes,
// and 1 kibibyte (Kib) is 1024 bytes.
#define Kib(x) (1024*(x))
#define Mib(x) (1024*(Kib(x)))
#define Gib(x) (1024*(Mib(x)))
// Probably won't use this one ever, but not like it costs anything to
// have it.
#define Tib(x) (1024*(Gib(x)))

// Get machine epsilon. If this matters for other things, I'll add them,
// but we're probably only really worried about epsilon for float and
// double in most scenarios. The two WILL be different, so I've made
// different functions rather than overloading. This won't change during
// any given compilation session, though, so we're just gonna leave it
// here in the header to create a global.
//
// Side note: I used these to test a square root function, even though I
// knew I wouldn't actually use it in this library, since the builtin
// already uses a square root machine instruction, which makes it about
// as fast as you can get.
//
float getEpsilonFloat (void) {
	float max         = 1.0f;
	float min         = 0.0f;
	float test        = 0.0f;
	float onePlusTest = 0.0f;
	int   i           = 0;

	for (i = 0; i < 100000; ++i) {
		test = (max + min) / 2.0f;
		onePlusTest = 1.0f + test;
		if (onePlusTest == 1.0f) min = test;
		else max = test;
	}
	return max;
}
float epsilonFloat = getEpsilonFloat ();

double getEpsilonDouble (void) {
	double max         = 1.0;
	double min         = 0.0;
	double test        = 0.0;
	double onePlusTest = 0.0;
	int    i           = 0;

	for (i = 0; i < 100000; ++i) {
		test = (max + min) / 2.0;
		onePlusTest = 1.0 + test;
		if (onePlusTest == 1.0) min = test;
		else max = test;
	}
	return max;
}
double epsilonDouble = getEpsilonDouble ();

/********************************************************************
 **                                                                **
 **                    MATHEMATICAL FUNCTIONS                      **
 **                                                                **
 **                                                                **
 *******************************************************************/
// TODO(randy): Overload for all integral types.

// This should overload the math.h pow() to also work with integers.
int pow (int base, int exp) {
	int result = 1;
	while (exp) {
		if (exp & 1) result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

// Helper function to create sign-bit-based masks borrowed from
// https://hbfs.wordpress.com/2008/08/05/brancheless-equivalents-of-simple-functions,
// who borrowed it from a Motorola 6809 instruction for (s)ign (ex)tend:
inline uint sex (int x) {
	return x >> (CHAR_BIT * sizeof (int) - 1);
}
	/*
	 * This uses cbw instructions, but makes assumptions about the
	 * architecture. I might be able to use macros to get everything
	 * right, but I'm not likely to be leaving 32- and 64-bit
	 * little-endian machines any time soon, and that would be a lot
	 * harder than, say, including another #elif to get 8- and 16-bit
	 * wordsizes was. For now, we'll just use the bitshift version, since
	 * it works fine on a regular PC.
	 *
	 * sex() is necessary to get a lot of the rest of this working, so it
	 * has to come first.
	 */
	/*union {
#if sizeof(long) == 2*sizeof(int)
		long w;
#elif sizeof(long long) == 2*sizeof(int)
		long long w;
#else
		// cannot determine the right size
	return x >> (CHAR_BIT * sizeof (int) - 1);
#endif
		struct {int lo, hi;}
	} z = {.w=x};
	return z.hi;*/

// Nonbranching math functions for int.
// Nonbranching version of abs().
inline int abs (int x) {return (x ^ sex(x)) - sex(x);}

// Not hard to make a float version, but it turns out a float version's
// basically useless, too.

//
// Okay, why is this working on my Windows VM, but not on my main Linux
// box? This doesn't use anything but C primitives.
//
// inline float abs (float x) {
//		char *sign = (char*) &x + sizeof (float) - 1;
//		char mask = (*sign) >> 1;
//		*sign = ((*sign) ^ mask) - *sign;
//		return (x);
// }
//
// I'm seriously annoyed by this. I don't think endianness would affect
// this (the compiler's supposed to take care of that), but I've tried
// realigning *sign and shifting mask by different amounts in both
// directions, and at best I get back what I put in; most of the time, I
// get back garbage or evidence that I'm only altering the lower-order
// bits of the mantissa (eg: 1.3 returns 1.297784 or whatever).
//
// Experimentation shows I get similar errors when using this on 32-bit
// Windows. So weird.
//

// If I ever need a nonbranching float absval, uncomment:
// inline float abs (float x) {int y = ((int&)x & 0x7fffffff); return; (float&) y;
// Unfortunately, the casting requires an lvalue, while the operation
// returns an rvalue, so I do still need to store y.
// TODO: MACRO code to change the mask for the system wordsize, and
// overload for double.
inline int floor  (int a, int b) {return b + ((a - b) & sex (a-b));}
inline int ceil   (int a, int b) {return a + ((b-a) & ~sex (b-a));}

/********************************************************************
 **                                                                **
 **                          UTILITIES                             **
 **                                                                **
 **                                                                **
 *******************************************************************/
// Swap values without storing an extra variable. (XOR). This works for
// all primitives, including float and pointers, but you have to cast them
// right:
// swap ((int*)&float, (int*)&float);
// swap((int*)(&pointer), (int*)(&pointer));
// However, info may be lost if sizeof(int)!=PTR_SIZE. Therefore, we also
// implement swapPtr(). If using swap() on a pointer doesn't work, use
// swapPtr and it will work. Just remember, it doesn't always work on
// arrays, probably because of how their members have to be initialized.
//
//KNOWN ERRORS:
//
// swap () doesn't move pointers within a struct. So, swap
// ((int*)(&structa), (int*)(&structb)) will result in all values being
// swapped, but all pointers (including all strings!) staying the same.
//
// The previous warning applied before I added checking if both operands
// were the same pointer; after I added that check, only the first member
// of a struct was swapped. I'm not sure why, when I'm swapping the
// address the pointer variable points to... This is true of both structs
// and typedef'd structs.
//
// Neither swap() nor swapPtr() can swap an array. I'm still trying to
// figure that one out.
//
// These warnings are also true of swapPtr.
//
void swap (int* x, int* y) {
	if (x == y) return; // x ^ x = 0, which would be bad!
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

// To swap pointers, cast either (void**)(&ptr) or &((void*)ptr)
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
// Print bits for debugging. (Makes it easier to see what's going on with
// flags and masks!)
// Someday, I may overload for int, float, etc., but that'll take
// some MACRO-ing to be platform-portable. For now,
// printbits((int&)float_input) is probably enough.
void printbits (uint8 input);
void printbits (uint16 input);
void printbits (uint32 input);
void printbits (uint64 input);
void printbits (int8 input);
void printbits (int16 input);
void printbits (int32 input);
void printbits (int64 input);

// Block on user input. ANY user input, not just the return key.
void pressAnyKey (void);

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

#if defined (__unix__) || defined (__linux__) || (defined (__APPLE__) && defined (__MACH__)) || defined (__FreeBSD__) // posix check
void pressAnyKey (void) {
	// Blocks on user input... but ANY user input, not specifically the
	// RETURN key.
	struct termios info;
	struct termios oldinfo;
	tcgetattr (0, &info);             // get a termios to change
	tcgetattr (0, &oldinfo);          // get a termios for resetting
	info.c_lflag &= ~ICANON;          // disable canonical mode
	info.c_cc[VMIN] = 1;              // wait until a keystroke is available
	info.c_cc[VTIME] = 0;             // no timeout
	tcsetattr (0, TCSANOW, &info);    // set immediately
	getchar ();                       // wait on user input
	tcsetattr (0, TCSANOW, &oldinfo); // reset terminal
}
#endif // posix check

#define RAG_SNIPPETS
#endif // header guard


//#define DEBUG
#ifdef DEBUG
/********************************************************************
 **                                                                **
 **                             MAIN                               **
 **                 FOR DEBUGGING PURPOSES ONLY                    **
 **                                                                **
 *******************************************************************/

int main () {
	printf ("epsilonDouble is %.30lf\n", epsilonDouble);
	printf ("epsilonFloat is %.20f\n", epsilonFloat);
	return 0;
}
#endif // DEBUG

