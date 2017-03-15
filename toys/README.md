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
* __ePiI.py: Same as above, but in python, because why not?
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

Watch this space for more silly little useless one-hour-type projects!
