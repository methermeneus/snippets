// I just kinda wanted to try this out.
// It's well-documented and just a bunch of math, so the code is
// technically trivial.

// SHA1 works by:
//		Padding the message to a multiple of 512 bits by appending the
//			bit 1, then the bit 0 repeated until the message size is 64
//			bits short of a multiple of 512, then appending the original
//			message's length (in bits) represented as a 64-bit big-endian
//			integer.
//		Taking a standard starting 512-bit value and breaking it into 5
//			4-byte integers
//		Subjecting these 5 integers to the SHA1 compression function,
//			along with the message bits, 80 times to produce a
//			pseudo-random bitstring.
//		Adding the resulting 5 integers to the pre-compression 5 integers
//			without carries, which deliberately loses information, making
//			it more difficult to backtrack to the original value
//		Repeating the previous two steps until the message has been
//			exhausted.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen (), strcat ()
#include <unistd.h> // getopt ()
#include "../snippets.cpp"

#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)			\
{										\
	(n) = ((uint32)(b)[(i)    ] << 24)  \
        | ((uint32)(b)[(i) + 1] << 16)  \
		| ((uint32)(b)[(i) + 2] <<  8)  \
		| ((uint32)(b)[(i) + 3]      ); \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)			\
{										\
	(b)[(i)    ] = (uint8)((n) >> 24);  \
	(b)[(i) + 1] = (uint8)((n) >> 16);  \
	(b)[(i) + 2] = (uint8)((n) >>  8);  \
	(b)[(i) + 3] = (uint8)((n)      );  \
}
#endif

// May migrate to snippets:
int isLittleEndian (void) {
	uint x = 1;
	return (int)(*((char*)&x));
}

uint32 rotL (uint32 value, uint count) {
	const uint mask = (8 * sizeof (value) - 1);
	count &= mask;
	return (value << count) | (value >> ((count * -1) & mask));
}
uint32 rotR (uint32 value, uint count) {
	const uint mask = (8 * sizeof (value) - 1);
	count &= mask;
	return (value >> count) | (value << ((count * -1) & mask));
}

typedef struct Sha1Vars {
	uint32 h[5];
	uint32 s[2];
	uint8  buffer[64];
} state;

uint32 sha1LittleEndian (uint32 *message, int64 messageLen, uint32* result);
uint32 sha1BigEndian (uint32 *message, int64 messageLen, uint32* result);

uint32 hash (uint32 *message, int64 messageLen, uint32 *result) {
	if (isLittleEndian ()) sha1LittleEndian (message, messageLen, result);
	else sha1BigEndian (message, messageLen, result);
	return (*result);
}


int main (int argc, char** argv) {
	return (0);
}

uint32 sha1LittleEndian (uint32 *message, int64 messageLen, uint32* result) {
	uint32 *messageWC = (uint32*) malloc ((messageLen / 8)); // working copy
	memcpy ((void*) messageWC, (void*) message, (size_t) (messageLen / 8));
	state loopState;
	loopState.s[0] = 0;
	loopState.s[1] = 0;
	loopState.h[0] = 0x67452301;
	loopState.h[1] = 0xEFCDAB89;
	loopState.h[2] = 0x98BADCFE;
	loopState.h[3] = 0x10325476;
	loopState.h[4] = 0xC3D2E1F0;

	state hashState = loopState;


	uint8 data[64];

	uint32 bytes[16], A, B, C, D, E;
	int i,j,k = 0;
	for (i = 0; i < 16; ++i) {
		GET_UINT32_BE (bytes[i], data, (i*4));
	}

	// These are traditionally done as defines; I don't understand why,
	// since it introduces points of confusion and failure (the C
	// preprocessor), for very little return in terms of performance on
	// an already fairly simple operation (for a computer). In fact,
	// between the fact that this is all strings of primitive ALU
	// operations and the inlining, this actually is probably exactly the
	// same in the CPU.
	//
	// Above notes left for posterity, but apparently this implementation
	// takes advantage of #undef to redefine some of these.
	
	inline uint32 S (uint32 x, int n) {
		return ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)));
	}

	inline uint32 F (uint32 x, uint32 y, uint32 z) {
		return (z ^ (x & (y ^ z)));
	}

	// Well, I'm okay with defining K, under these circumstances.
#ifndef K // In case we run multiple hashes
#define K 0x5A827999
#else
#undef K
#define K 0x5A827999
#endif

	// I think we might need to #define R as well; or, at least, it'd
	// take me a while to extract it from the #define.
#ifndef R()
#define R(t)												\
(															\
	temp = bytes[(t -  3) & 0x0F] ^ bytes[(t-8) & 0x0F] ^   \
  	       bytes[(t - 14) & 0x0F] ^ bytes[ t    & 0x0F],    \
    (bytes[t & 0x0F] = S(temp, 1))                          \
)
	
	// P does two operations, so it does need pointers, since C doesn't
	// do polymorphism. C++ would probably be fine, though.
	inline void P (uint32 *a, uint32 *b, uint32 *c, uint32 *d uint32 *e, uint32 *x) {
		(*e) += S (*a, 5) + F (*b, *c, *d) + K + x;
		(*b) = S (b, 30);
	}

	A = loopState->s[0];
	B = loopState->s[1];
	C = loopState->s[2];
	D = loopState->s[3];
	E = loopState->s[4];

	P (A, B, C, D, E, bytes[ 0]);
	P (E, A, B, C, D, bytes[ 1]);
	P (D, E, A, B, C, bytes[ 2]);
	P (C, D, E, A, B, bytes[ 3]);
	P (B, C, D, E, A, bytes[ 4]);
	P (A, B, C, D, E, bytes[ 5]);
	P (E, A, B, C, D, bytes[ 6]);
	P (D, E, A, B, C, bytes[ 7]);
	P (C, D, E, A, B, bytes[ 8]);
	P (B, C, D, E, A, bytes[ 9]);
	P (A, B, C, D, E, bytes[10]);
	P (E, A, B, C, D, bytes[11]);
	P (D, E, A, B, C, bytes[12]);
	P (C, D, E, A, B, bytes[13]);
	P (B, C, D, E, A, bytes[14]);
	P (A, B, C, D, E, bytes[15]);
	P (E, A, B, C, D, R(16));
	P (D, E, A, B, C, R(17));
	P (C, D, E, A, B, R(18));
	P (B, C, D, E, A, R(19));

#undef F
#undef K
#define F (x,y,x) (x ^ y ^ z)
#define K 0x6ED9EBA1

	return (*result);
}

uint32 sha1BigEndian (uint32 *message, int64 messageLen, uint32* result) {
	return (*result);
}
