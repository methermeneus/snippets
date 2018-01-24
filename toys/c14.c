#include <stdio.h>
#include <math.h>

int main (void) {

	double mass = 5.9722 * pow (10, 24); // in kg
	double volume = 1.0 * pow (10, 22); // in L
	double density = 2.64483; // C12's density is 2.2670g/cc; I took the expedient approach of cross-multiplying:
		// (2.2670/12)=)x/14). This yields (more exactly (26448 1/3)E-5).
		// That's probably not correct, but good enough for my purposes.
	density *= 1000; // cc->L
	double halflife = 5730; // in years
	int periods = 0;

	FILE* halves;
	halves = fopen ("half_lives.txt", "w");

	fprintf (halves, "Time to eliminate an earth-mass of C14:\nMass = %.0lf kg; half life = %4.0lf yrs\n", mass, halflife);
	while (mass > 0.001) {
		fprintf (halves, "%2d periods:\t\t%6.0lf years:\t\t%.3lf kg C14 remaining\n", periods, (double) periods * halflife, mass);
		mass = mass / 2;
		++periods;
	}

	periods = 0;
	mass = density * volume; // in g
	mass = mass / 1000; // in kg
	fprintf (halves, "\n\n\nTime to eliminate an earth-volume of C14:\nMass = %.0lf kg; half life = %4.0lf yrs\n", mass, halflife);

	while (mass > 0.001) {
		fprintf (halves, "%2d periods:\t\t%6.0lf years:\t\t%.3lf kg C14 remaining\n", periods, (double) periods * halflife, mass);
		mass = mass / 2;
		++periods;
	}

	fclose (halves);

	return (0);
}
