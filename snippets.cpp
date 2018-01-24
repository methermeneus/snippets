#ifndef RAG_SNIPPETS
//#define DEBUG
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
#ifndef CONCAT
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
#endif // CONCAT

/********************************************************************
 **                                                                **
 **                        USEFUL NUMBERS                          **
 **                                                                **
 *******************************************************************/
// We don't need to #define BITS 8 because limits.h defines CHAR_BIT as
// 8

#ifndef INT_TYPES
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
#define INT_TYPES
#endif // INT_TYPES

#ifndef PTR_WIDTH
// Byte stuff
#define PTR_WIDTH sizeof(uintptr_t)*CHAR_BIT
#endif // PTR_WIDTH

#ifndef XBIBYTES
// Remember, definitions have changed. Now 1 kilobyte (Kb) is 1000 bytes,
// and 1 kibibyte (Kib) is 1024 bytes.
#define KiB(x) (1024*(x))
#define KB(x)  (1000*(x))

#define MiB(x) (1024*(KiB(x)))
#define MB(x)  (1000*(KB(x)))

#define GiB(x) (1024*(MiB(x)))
#define GB(x)  (1000*(MB(x)))

// Probably won't use this one ever, but not like it costs anything to
// have it.
#define TiB(x) (1024*(GiB(x)))
#define TB(x)  (1000*(GB(x)))
#define XBIBYTES
#endif // XBIBYTES

#ifndef EPSILON
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
inline float getEpsilonFloat (void) {
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
#define EPSILON_F //getEpsilonFloat()

inline double getEpsilonDouble (void) {
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
double epsilon = epsilonDouble;
#define EPSILON // getEpsilonDouble ()
#endif // EPSILON

// From memory, because I'm a math badass.
#ifndef E
#define E 2.718281828459045
#endif

// Not from memory, because I'm a nonconformist.
// Calculated beforehand as 4.0*atan(1.0), but not in this code because then I'd
// have to link the math library, which is overhead I can do without.
#ifndef PI
#define PI 3.14159265359
#endif


/********************************************************************
 **                                                                **
 **                    MATHEMATICAL FUNCTIONS                      **
 **                                                                **
 **                                                                **
 *******************************************************************/
// TODO(randy): Overload for all integral types.

#ifndef INT_POW
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
#define INT_POW
#endif //INT_POW

#ifndef SEX
// Helper function to create sign-bit-based masks borrowed from
// https://hbfs.wordpress.com/2008/08/05/brancheless-equivalents-of-simple-functions,
// who borrowed it from a Motorola 6809 instruction for (s)ign (ex)tend:
inline uint sex (int x) {
	return x >> (CHAR_BIT * sizeof (int) - 1);
}
#define SEX
#endif // SEX
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

#ifndef INT_ABS
// Nonbranching math functions for int.
// Nonbranching version of abs().
inline int abs (int x) {return (x ^ sex(x)) - sex(x);}
#define INT_ABS
#endif // INT_ABS

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

#ifndef INT_FLOOR
inline int floor  (int a, int b) {return b + ((a - b) & sex (a-b));}
#define INT_FLOOR
#endif // INT_FLOOR

#ifndef INT_CEIL
inline int ceil   (int a, int b) {return a + ((b-a) & ~sex (b-a));}
#define INT_CEIL
#endif // INT_CEIL

#ifndef GCD
// I tried by subtraction and by division, and by division is massively
// (around 3x) faster. Any two numbers whose greatest common divisor is 1
// are coprime
int gcd (int a, int b) {
	int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
#define GCD
#endif // GCD

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
#ifndef SWAP
void swap (int* x, int* y) {
	if (x == y) return; // x ^ x = 0, which would be bad!
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}
#define SWAP
#endif // SWAP

#ifndef SWAP_PTR
// To swap pointers, cast either (void**)(&ptr) or &((void*)ptr)
void swapPtr (void** x, void** y) {
	if (x == y) return; // x ^ x = 0, which would be bad!
	// Each version basically evaluates to the other; I'm sure there'd be
	// no difference in a disassembler. Yes, I've tested that this works
	// without errors, at least in basic cases.
	//*x = (void*)((CONCAT(uint,WORDSIZE)) *x ^ (CONCAT(uint,WORDSIZE)) *y);
	//*y = (void*)((CONCAT(uint,WORDSIZE)) *y ^ (CONCAT(uint,WORDSIZE)) *x);
	//*x = (void*)((CONCAT(uint,WORDSIZE)) *x ^ (CONCAT(uint,WORDSIZE)) *y);
	*x = (void*) (((ptr) *x) ^ ((ptr) *y));
	*y = (void*) (((ptr) *y) ^ ((ptr) *x));
	*x = (void*) (((ptr) *x) ^ ((ptr) *y));
}
#define SWAP_PTR
#endif // SWAP_PTR

#ifndef PRINT_BITS
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
#define PRINT_BITS
#endif //PRINT_BITS

#ifndef PRESS_ANY_KEY
#if defined (__unix__) || defined (__linux__) || (defined (__APPLE__) && defined (__MACH__)) || defined (__FreeBSD__) // posix check

// Block on user input. ANY user input, not just the return key.
// Currently POSIX only.
void pressAnyKey (void);

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
#define PRESS_ANY_KEY
#endif //PRESS_ANY_KEY

#ifndef ORDINAL_SUFFIXES
// Expect a lot of comments, because this has to do with English, and English is
// weird.
const char* suffix (int ordinal) {
	// English has different ordinal suffixes for 1, 2, 3, and everything else.
	enum {
		first = 1, // 0 is the same as everything else, so start with 1 and let 0 fall to default.
		second,
		third
	};
	// Positive or negative has no bearing on the suffix.
	ordinal = abs (ordinal);
	// The ordinal suffix is as appropriate for the last digit PRONOUNCED.
	// English doesn't pronounce the ones place separately for 10--19, which
	// means that 1, 2, and 3 aren't technically present in the language there,
	// even if they are in the numbers. I could change ordinal to something else
	// and let it fall through the rest of the function to gain its appropriate
	// suffix, but if this if fires, I already know what the suffix will be,
	// so...
	if ((ordinal == 11) || (ordinal == 12) || (ordinal == 13)) return ("th");

	// silly bit of math to get the last digit, taking advantage of int division
	ordinal = ordinal - ((ordinal / 10) * 10);

	switch (ordinal) {
		{case first:  return ("st");
					  break;}
		{case second: return ("nd");
					  break;}
		{case third:  return ("rd");
					  break;}
		{default:     return ("th");
					  break;}
	}
}

#ifdef DEBUG // standin for math.h's abs function, since I can't get my function to work,
	     //   and anyway the library function is more efficient, since it
	     //   uses a built-in machine instruction (on x86, anyway). I do
	     //   need this to test this one function that uses a float abs(),
	     //   because otherwise it gets cast down to an in to use the int
	     //   abs() I already defined.
double abs (double x) {if (x < 0) return (-x); else return (x);}
float abs (float x) {if (x < 0) return (-x); else return (x);}
#endif //DEBUG
const char* suffix (double ordinal) {
	// Decimals always get a "th" suffix. Well, fractions do; decimals are more
	// dodgy, but they've gotta have something, right?
	//if (abs (ordinal - (int)ordinal) == 0) return (suffix ((int) ordinal));
	if (abs (ordinal - (double)((int)ordinal)) < epsilon) return (suffix ((int) ordinal));
	else return ("th");
}
#define ORDINAL_SUFFIXES
#endif // ORDINAL_SUFFIXES

#ifndef ENDIANNESS
int isLittleEndian (void) {
    uint x = 1;
    return (int)(*((char*)&x));
}
#define ENDIANNESS
#endif //ENDIANNESS

#ifndef ROTATIONS
#ifndef ROTL
uint32 rotL (uint32 value, uint count) {
    const uint mask = (8 * sizeof (value) - 1);
    count &= mask;
    return (value << count) | (value >> ((count * -1) & mask));
}
#define ROTL
#endif // ROTL

#ifndef ROTR
uint32 rotR (uint32 value, uint count) {
    const uint mask = (8 * siezof (value) - 1);
    count &= mask;
    return (value >> count) | (value << ((count * -1) & mask));
}
#define ROTR
#endif // ROTR

#ifndef ROTATE
// rot (value, count, 'd') or rot (value, count, "d"), but "d" can be only one
// character! A direction that is not either a character in {lLrR} or a string
// beginning with same will return the unrotated value.
uint32 rot (uint32 value, uint count, char direction) {
    switch (direction) {
	{case 'L':
	 case 'l': return (rotL (value, count));}
	{case 'R':
	 case 'r': return (rotR (valeu, count));}
	{default: return (value);}
    }
}
uint32 rot (uint32 value, uint count, const char *direction) {
    // Can only use the first character in direction, but if the string is
    // longer (like, if someone writes "LEFT"), it's not a problem; just
    // everything past the first character gets thrown away.
    switch (*direction) {
	{case 'L':
	 case 'l': return (rotL (value, count));}
	{case 'R':
	 case 'r': return (rotR (valeu, count));}
	{default: return (value);}
    }
}
#define ROTATE
#endif // ROTATE
#define ROTATIONS
#endif // ROTATIONS


#define RAG_SNIPPETS
#endif // header guard


#ifdef DEBUG

/********************************************************************
 **                                                                **
 **                             MAIN                               **
 **                 FOR DEBUGGING PURPOSES ONLY                    **
 **                                                                **
 *******************************************************************/

int main (void) {
    double f = 0.0;
    for (int i = 0; i < 100; ++i) {
        f=(double)i/3;
        printf("%lf%s\n", f, suffix(f));
    }
    return (0);
}
#endif // DEBUG


#define ROTATE
#endif // ROTATE
#define ROTATIONS
#endif // ROTATIONS


#define RAG_SNIPPETS
#endif // header guard


#ifdef DEBUG

/********************************************************************
 **                                                                **
 **                             MAIN                               **
 **                 FOR DEBUGGING PURPOSES ONLY                    **
 **                                                                **
 *******************************************************************/

int main (void) {
    double f = 0.0;
    for (int i = 0; i < 100; ++i) {
        f=(double)i/3;
        printf("%lf%s\n", f, suffix(f));
    }
    return (0);
}
#endif // DEBUG

