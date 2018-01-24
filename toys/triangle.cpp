/* =============================================================================*
*                                                                               *
* FILE: triangle.cpp                                                            *
* DATE: 2018-01-23                                                              *
* REVISION:                                                                     *
* CREATOR: R. A. Grant (methermeneus@gmail.com)                                 *
*	NOTICE: (C) Copyright 2018 by Wholly Crap Productions.                      *
*                                                                               *
* DESCRIPTION: Given a whole number input, returns a triangle number and an     *
*   appropriate triangle. Terminal-only, POSIX-only.                            *
*   If no input is given, provides a sample of the 9th triangle number, 45.     *
*                                                                               *
*===============================================================================*/

#include "../snippets.cpp" // suffix()
#include <cstdio>		   // printf(), fprintf(), stderr
#include <sys/ioctl.h>	   // ioctl(), struct winsize, TIOCGWINSZ, TIOCGSIZE
#include <cctype>		   // isdigit()
#include <cstdlib>		   // atoi()

int main (int argc, char** argv, char** env) {
	int input (0);
	// We don't need much input handling; just take 0 or 1 arguments, make sure
	// it's a positive int.
	printf ("%d\n", argc);
	switch (argc) {
		{case 1:  input = 9;
				  break;
		}
		{case 2:  char *checker (argv[1]);
				  while (*++checker) {
					  if (!isdigit (*checker)) {
						  fprintf (stderr, "Error, %s is not a whole number.\n", argv[1]);
					  	  return (-1);
					  }
				  }
				  input = atoi (argv[1]);
				  break;
		}
		{case 3:  fprintf (stderr, "Error, too many arguments: Expected 1, received %d\n", argc - 1);
				  return (-2); // I don't think we need to break after a return...
		}
		{default: fprintf (stderr, "Error, reached a portion of the program that should be unreachable!\n");
				  return (9001); // It's over 9000!
		}
	}
	// And one more little check, just to keep it from getting ugly in the
	// terminal.
	struct winsize xy;
#ifdef TIOCGWINSZ
	ioctl (1, TIOCGWINSZ, &xy);
#elif TIOCGSIZE
	ioctl (1, TIOCGSIZE, &xy);
#else
	// I think it's doubtful the width will be less than this outside of a phone
	// screen.
	xy.ws_col = 60;
#endif // TIOCG[WIN]S[I]Z[E]
	if ((input * 2) > xy.ws_col) {
		fprintf (stderr, "Error, input value is too large.\n");
		fprintf (stderr, "Twice input is %d, but terminal width is only %d.\n", input * 2, xy.ws_col);
		return (-3);
	}

	// The actual point of this thing!
	int position (0);
	int total (0);
	int pos (0);
	for (int i (1); i <= input; ++i) {
		position = input - i;
		total += i;
		for (pos = 0; pos < position; ++pos) printf (" ");
		for (pos = 0; pos < i; ++pos) printf ("* ");
		printf ("\n");
	}
	printf ("\nThe %d%s triangle number is %d.\n", input, suffix(input), total);

	return (0);
}
