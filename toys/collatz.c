// Another math thing: Given a number, output the number of steps to get
// to 1 via the Collatz conjecture.
// Why, yes, I do think of these by watching Numberphile, why do you ask?

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../snippets.cpp"

int main (int argc, char* argv[]) {
	if (argc < 2) {
		fprintf (stderr, "Error, requires a positive number.\n");
		return (-1);
	} else if (argc > 2) {
		fprintf (stderr, "Error, too many arguments.\n");
		return (-2);
	}

	int i = 0;
	uint64 number = 0;
	while (argv[1][i] != 0) {
		if (!isdigit ((int)(argv[1][i]))) {
			fprintf (stderr, "Error, argument must be a positive integer.\n");
			return (-3);
		}
		++i;
	}
	number = atoi (argv[1]);
	if (number < 1) {
		fprintf (stderr, "Error, argument must be a positive integer.\n");
		return (-4);
	}
	int steps = 0;
	while (number != 1) {
		printf ("%lu -> ", number);
		if (number % 2) number = (number * 3) + 1;
		else number /= 2;
		printf ("%lu\n", number);
		++steps;
	}
	printf ("%d reduced to 1 in %d step%s\n", atoi(argv[1]), steps, steps == 1 ? "." : "s.");
	return 0;
}
