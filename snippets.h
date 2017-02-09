#ifndef SNIPPETS_H
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
 **                                                                **
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

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


/********************************************************************
 **                                                                **
 **                    MATHEMATICAL FUNCTIONS                      **
 **                                                                **
 **                                                                **
 *******************************************************************/
// TODO(randy): Overload for all integral types.

// This should overload the math.h pow() to also work with integers.
int   pow (int   base, int   exp);

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
// all variables, including float and pointers, but you have to cast them
// right:
// swap ((int*)&float, (int*)&float);
// swap((int*)(&pointer), (int*)(&pointer));
// However, info may be lost if sizeof(int)!=PTR_SIZE. Therefore, we also
// implement swapPtr(). If using swap() on a pointer doesn't work, use
// swapPtr and it will work. Just remember, it doesn't always work on
// arrays, probably because of how their members have to be initialized.
//
void swap (int* x, int* y);
// To swap pointers, cast either (void**)(&ptr) or &((void*)ptr)
void swapPtr (void** x, void** y);

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

#define SNIPPETS_H
#endif




/********************************************************************
 **                                                                **
 **                                                                **
 **                                                                **
 **                                                                **
 *******************************************************************/
