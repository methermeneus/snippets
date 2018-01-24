# My toys

These are just some programs I made for fun. I realize some of them might just look like
school assignments, but I'm not in school for programming; I just think it's amusing to
fiddle around with these things sometimes. A lot of the time, the fun is specifically in
forcing C[++] to do things.

## NOTE:
These are here for my own archive. If you find something useful, great, but you probably
won't. Also, it's a good thing these are all so short, since I don't bother to keep my
formatting very clean.

## FILES:
* __countdown.cpp__: Clears the terminal and displays a centered countdown. I did this one
	mostly just to play around with the terminal manipulators.
* __ePiI.c__: Checks if C gets the right answer for e^πi. Answer: Not without some
	fiddling, so this also checks if the difference between the expected result and the
	actual result is significant (ie: greater than ε), and only outputs the expected answer
	if the difference is insignificant.
* __ePiI.py__: Same as above, but in python, because why not?
* __estimatePiByGCD.c__: After watching Matt Parker's 2017 Pi Day video, wherein he
	estimates pi from the ratio of coprimes to non-coprimes within a set of 500 pairs of
	random numbers between 1 and 120 (by laboriously rolling a pair of d-120s 500 times), I
	was inspired to see how well a computer could do, so I paused the video and checked.
	Then I hit play again, and he did the same thing (albeit, with Excel instead of C).
	Whoops. Anyway, it turns out that even using 2147483647 as my max (by using rand()
	unadorned) and millions of pairs, the estimates still don't get much better than just a
	couple hundred. Just using, say twenty, however, can give you numbers like 2.4 and 4.0,
	which are obviously horrible estimates; 150 or more should mostly keep you within 10%.
	(See the video here: https://www.youtube.com/watch?v=RZBhSi_PwHU )
* __collatz.c__: First Matt Parker, now Numberphile? Given a number, output the number of
	steps to reach 1 via the Collatz conjecture.
* __fizzbuzz.cpp__: Because I heard mention that some prospective programmers can't do it
	even after four years of college. Screw dat. Twenty minutes, including error checking.
	Five minutes not including error checking.
* __sha1.c__: Basic (and probably naive) implementation of the sha1 hash, because I
	happened upon an explanation of the math (Computerphile, this time) and wanted to see if
	I could. Sha1 is useful, but having my own personal implementation of it is not, hence
	toys, although it does include a few bits I may migrate to snippets.
* __c14.c__: Because I heard someone (Kent Hovind, maybe?) making fun of C-14 dating by
	claiming a ball of C-14 the size of the earth would take some silly amount of time to
	disappear, I decided to see just how long it would actually take. The calculations are
	very basic, but I did go so far as to calculate for both a C-14 planet with Earth's mass
	and one with Earth's volume.
* __triangle.cpp__: Prints the nth triangle number and its corresponding triangle (limited
	by terminal width). If the caller doesn't provide a number, prints a demonstration of
	the ninth triangle number, which is 45. For fun, try printing the 36th triangle number!

Watch this space for more silly little useless one-hour-type projects!
