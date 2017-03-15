/*

This program checks if builtin math functions get the right answer for
e^(pi*i) (which should be -1) within a margin of error of machine
epsilon. If it works, print "e^pi*i == -1", else print "e^pi*i != -1"

Requires three tests:
	1) is i nonexistent or at least insignificant (since we're working
	with floating point numbers, after all). if i < epsilon, good enough.
	2) is r exactly -1 (this actually should be equal, not just within
	epsilon). Best test: is ceil (r) == floor (r)? (If r != -1, ceil ==
	floor + 1. If the difference is different, something weird is
	happening)
	3) 2 actually only checks that r is an integer value (mathematically;
	computationally, it's probably still stored as a float). You still
	need to look at the output to make sure that the value is -1. I know
	the computer could just check if r == -1, but for some reason I like
	to be able to do that last check visually. These versions all
	truncate r in one way or another, so you can't be certain it's
	exactly right without some assistance, hence checks 1 and 2. If
	the output is "e^pi*i == -1", then you're good. If it's "!=" or a
	value other than -1, then you have problems.
*/

#include <stdio.h>
#include <math.h> // math functions; compile with -lm
#include <complex.h> // complex numbers (I) and complex functions (cexp, creal, cimag); compile with -lm
#include "../snippets.cpp" /* my snippets file; contains machine epsilon
						 * for double and float. Although these are all
						 * doubles, I had trouble when I compared to
						 * doubleEpsilon, so we're using floatEpsilon
						 * here. Probably has something to do with the C
						 * codebase being old enough to have some
						 * float-specific stuff in there somewhere.*/
int main (void) { // no need for args here
	double pi = 4.0 * atan (1.0); // pi to more places than I'd probably
			// type it out; maybe move this to the actual snippets file?
	double complex eToThePiI = cexp (I * pi);
	double result = creal (eToThePiI);
	int retVal = 0;
	// Is i insignificant?
	cimag (eToThePiI) < epsilonFloat ? retVal = retVal : retVal = -1;
	// Is r an integer value? (If i was significant, don't remove the
	// error value just because this part is okay; it has to pass all
	// tests to be okay.)
	ceil (result) == floor (result) ? retVal = retVal : retVal = -1;
	// Now doesn't that look like a nice arcane bit of C code?
	printf ("e^pi*i %s %0.0lf\n", !retVal ? "==" : "!=", result);
	return (retVal);
}
