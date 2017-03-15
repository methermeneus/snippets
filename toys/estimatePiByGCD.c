#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h> // sqrt, atan
#include <ctype.h> // isdigit

// Estimate pi from the probability of two random numbers being coprime.
// (idea borrowed from Matt Parker (http://www.youtube.com/channel/UCSju5G2aFaWMqn-_0YBtq5A
// if x is the probability that two random numbers are coprime:
// 6 / pi ^ 2 = x
// 1 / pi ^ 2 = x / 6
// pi ^ 2 = 6 / x
// pi = sqrt (6 / x)

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

int main (int argc, char* argv[]) {
	if (argc > 2) {
		fprintf (stderr, "Error, too many arguments.\n");
		return (-1);
	}
	int testcases = 5000;
	int i = 0;
	int test1 = 0;
	int test2 = 0;
	if (argc == 2) {
		while (argv[1][i] != 0) {
			if (!isdigit((int)argv[1][i])) {
				fprintf (stderr, "Error, argument must be an integer.\n");
				return (-2);
			}
			++i;
		}
		testcases = atoi (argv[1]);
	}

	printf ("Testing %d cases.\n", testcases);
	srand (time (NULL));

	double coprimes = 0;
	double noncoprimes = 0;
	double pi = 4.0 * atan (1.0);

	for (i = 0; i < testcases; ++i) {
		test1 = rand();
		test2 = rand();
		if (!(gcd (test1, test2) -1)) {
			coprimes += 1;
		} else {
			noncoprimes += 1;
		}
	}
	printf ("calculated pi:\n");
	printf ("coprimes = %0.0lf\n", coprimes);
	printf ("non-coprimes = %0.0lf\n", noncoprimes);
	printf ("ratio = %lf\n", noncoprimes / coprimes);
	printf ("calculate pi to: %lf\n", sqrt (6.0 / (noncoprimes / coprimes)));
	printf ("actual pi    =   %lf\n", pi);
	
	return 0;
}
