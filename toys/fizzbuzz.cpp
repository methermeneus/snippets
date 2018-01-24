// Because I just saw Tom Scott's video on FizzBuzz, and I immediately
// came up with a better version in myhead:

#include <cstdio> // printf, fprintf
#include <cctype> // isdigit
#include <cstdlib> // atoi

void fizzbuzz (int x = 100) { // For extensibility: the common default is 100, but I can just provide a different number if the interviewer asks.
	// To change a test, change the value of fizz or buzz. To add more
	// tests, just copy fizz or buzz with different variable names and
	// values and copy a test block with the appropriate changes.
	int fizz (3);
	int buzz (5);
	int fizzbuzz (false); // Okay, fine, C[++] does make some things nonsensical. Just roll with this one.
	// By the way, Tom, "i" stands for "iterator." It's also just one of
	// the common starting points for an arbitrary number of mathematical
	// variables: a, b, c...; i, j, k...; x, y, z...
	for (int i = 1; i <= x; ++i) { // The game starts at 1, not 0, even if that seems weird for a computer program.
		// Also, the game ends at 100, inclusive.
		if (!(i % fizz)) {
			printf ("fizz");
			fizzbuzz = true;
		}
		if (!(i % buzz)) {
			printf ("buzz");
			fizzbuzz = true;
		}
		if (fizzbuzz) fizzbuzz = false;
		else printf ("%d", i);
		printf ("\n");
	}
}

int main (int argc, char** argv, char** env) {
	if (argc == 1) { // if the interviewer just asks for the default, just do 1--100 and exit.
		fizzbuzz (); // If the interviewer asks for different numbers in code, just put a number in the parens.
		return (0);
	} else if (argc > 2) { // if we screw up and input more than just the number of iterations
		fprintf (stderr, "Error: FizzBuzz only takes one numerical input, not %d.\n", argc-1);
		return (-1); // generic error
	} else {
		// make sure the argument is a number.
		char *c = argv[1];
		int digits (0);
		while (*c != '\0') {
			if (!isdigit (*c)) {
				fprintf (stderr, "Error: FizzBuzz only takes numerical input; \"%s\" is not valid.\n", argv[1]);
				return (-1);
			}
			else {
				++c; // See, pointer arithmetic isn't scary.
				++digits; // failsafe for ridiculously high numbers.
			}
		}
		// We don't get here if argv[1] isn't all digits:
		if (digits > 6) {// arbitrary limit of 999,999
			fprintf (stderr, "Error: At %d digits, %s is far too large a number for this simple interview program.\n", digits, argv[1]); // remember, this number is still stored in a string.
			return (-1);
		} else {
			fizzbuzz (atoi (argv[1]));
			return (1);
		// Yes, I know there's a bunch of nested if/else statements.
		// This is mostly for manual error catching, which is generally
		// better than throw/catch and can be changed to match the
		// company's error handling libraries.
		}
	}
}

// And I feel justified. Aside from a very silly mistake (for some
// reason, I tested if i == fizz and if i == buzz instead of if !(i %
// fizz) and if !(i % buzz), the kind of stupid mistake that comes from
// not thinking about what you're typing instead of not knowing what
// you're doing), all of my problems were in my error checking, which
// wasn't even part of the problem, but just something I threw in because
// I'm used to thinking about such things. That's on just one quick
// iteration. The fizzbuzz() funtion, which is what's really being
// tested, took me maybe five minutes.
//
