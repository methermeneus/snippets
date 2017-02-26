// Playing around with ASCII escapes

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "snippets.cpp"

int main (int argc, char *argv[]) {
	if (argc != 2) {
		fprintf (stderr, "Error, this program requires, one and only one, argument.\r\n");
		fprintf (stderr, "That argument indicates the number of seconds to run the timer.\r\n");
		fprintf (stderr, "Since this is a silly little program, try not to go over %d seconds, kay?\n", 60 * 5);
		return (1);
	}
	int i = 0;
	int j = 0;
	int kLen = strlen (argv[1]);
	for (i = 0; i < kLen; ++i) {
		if (!isdigit (argv[1][i])) {
			fprintf (stderr, "Error, this program only takes an integer argument.\n");
			return (2);
		}
	}
	int k = atoi (argv[1]);
	if (k > 60 * 5) {
		fprintf (stderr, "Seriously? You want to do this for more than 5 minutes? Edit the code a bit, then.\n");
		return ((5*60)+1);
	}
	struct winsize xy;
	ioctl (1, TIOCGWINSZ, &xy);
	int x = (xy.ws_col / 2) - 9;
	int y = xy.ws_row / 2;
	//for (i = 0; i < xy.ws_col; ++i) {
		//for (j = 0; j < xy.ws_row; ++j) {
			//printf ("\033[%d;%dH ", j, i);
		//}
	//}
	printf ("\033[?25l"); // hide cursor; last character is lowercase L
	printf ("\033[2J"); // Clear screen
	printf ("\033[%d;%dHCounting down: \0337", y, x);
	fflush (stdout);
	for (i = k; i > 0; --i) {
		switch (kLen) {
			case 1 :
				printf ("%d\0338", i);
				break;
			case 2:
				printf ("%2d\0338", i);
				break;
			case 3:
				printf ("%2d\0338", i);
				break;
			default:
				fprintf (stderr, "Wow, something weird went wrong here; this case shouldn't ever happen if my error checking is correct.\n");
				return (271828182); // Most digits of e I can get without going over INT MAX: 2147483647
		}
		fflush (stdout);
		usleep (1000000);
	}

	printf ("\033[1;31mBLASTOFF!!\033[0m\n");
	usleep (1000000);
	pressAnyKey ();
	printf ("\033[2J\033[;H\033[?25h"); // ?25h show cursor
	return 0;
}
