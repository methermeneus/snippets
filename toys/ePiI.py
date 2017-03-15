#!/usr/bin/python

#This program checks if builtin math functions get the right answer for
#e^(pi*i) (which should be -1) within a margin of error of machine
#epsilon. If it works, print "e^pi*i == -1", else print "e^pi*i != -1"
#
#Requires three tests:
#	1) is i nonexistent or at least insignificant (since we're working
#	with floating point numbers, after all). if i < epsilon, good enough.
#	2) is r exactly -1 (this actually should be equal, not just within
#	epsilon). Best test: is ceil (r) == floor (r)? (If r != -1, ceil ==
#	floor + 1. If the difference is different, something weird is
#	happening)
#	3) 2 actually only checks that r is an integer value (mathematically;
#	computationally, it's probably still stored as a float). You still
#	need to look at the output to make sure that the value is -1. I know
#	the computer could just check if r == -1, but for some reason I like
#	to be able to do that last check visually. These versions all
#	truncate r in one way or another, so you can't be certain it's
#	exactly right without some assistance, hence checks 1 and 2. If
#	the output is "e^pi*i == -1", then you're good. If it's "!=" or a
#	value other than -1, then you have problems.

from cmath import exp, pi, sqrt # exp (x) == pow (e, x). cmath has complex number versions of sqrt and exp.
from math import ceil, floor
from numpy import finfo # to get epsilon
x = exp (pi * sqrt (-1))
truth = ""
if x.imag >= finfo (float).eps: # is i insignificant (less than epsilon)?
	truth = " != "
else:
	truth = " == "
if ceil (x.real) != floor (x.real): # is r a float representation of an integer?
	truth = " != "

print "e^pi*i" + truth + repr (int (x.real))

