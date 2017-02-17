#C[++] Snippets
##By Randy Grant (methermeneus@gmail.com)

This is just some simple bits and bobs that I find useful or fun. Some I wrote, some is
snatched from the internet. I didn't remember to link everything I borrowed (believe it or
not, it's not all from Stack Exchange!), but it's all simple enough stuff that I don't
think anyone really cares about credit. All I did was compile it into this one file.

##Features:
###Numbers
* `CONCAT` macro for concatenating variable or function names. Useful for making `var1`,
`var2`, etc. when you'd rather not use an array for whatever reason.
* `typedef` various integer names to shorter names that are still easy to remember
* `typedef uintptr_t ptr` to make it easy to manipulate pointers as if they were
integers.
* `#define PTR_WIDTH sizeof(uintptr_t)*CHAR_BIT` to easily access the system's bus
width
* `#define Kib, Mib, Gib, Tib` for kibibytes, mebibytes, gibibytes, and tebibytes.
(Does anyone else miss when we could just call them kilobytes, etc. and
distinguish that from 1000 bytes?)
* `epsilonFloat` and `epsilonDouble` are globals containing the value of machine epsilon
	for float and double types. I may later factor these into lambdas or defines, but for
		now they have helper functions which are defined in the header.

###Math
* `int pow (int base, int exp)` for integer exponents
* `uint sex (int x)` to get the sign of an int (borrowed from
https://hbfs.wordpress.com/2008/08/05/brancheless-equivalents-of-simple-functions, who
borrowed it from a Motorola 6809 instruction)
* `int abs (int x)` for integer absolute values
* `int floor (int a, int b)` for integer floors
* `int ceil (int a, int b)` for integer ceilings

###Utilities
* `void swap (int* x, int* y)` swap integers in place without temporary storage. (XOR
swap). To swap floats, just cast them to int pointers (`swap ((int*)(&float1),
(int*)(&float2))`). Also works for pointers, but int may not be able to hold the whole
pointer.
* `void swapPtr (void** x, void** y)` swap pointers in place via XOR swap. Just cast
your pointer's address as a void. This uses `uintptr_t` (via `typedef uintptr_t ptr`),
which is guaranteed to hold an entire address, so it will always work for pointers.
The only exception is arrays, which cannot be swapped by an external function due to
the way their members must be initialized (at least on gcc; I haven't tested this
elsewhere).
* `void printbits (int input)` Print the actual bits of a variable. Currently
overloaded for all basic integer types, but it works just as well with casting types
of the same sizes (1, 2, 4, 8 bytes). Useful for debugging flags and masks.

##TODO:
- [ ] Overload all int functions for all integer types
- [ ] printf overloading for common arrays
- [ ] overload arrays to structs with length and maybe some methods _without_
templates, because screw C++ templates. Or, I can just wait 'till Jonathan Blow
releases JAI, I suppose.
- [ ] make a Vim shortcut to create comment boxes, so I can get rid of the one I
keep at the bottom of snippets.h for copy/pasting
- [x] overload `printbits()` for int64, because I apparently forgot
(**headdesk**) (`Apparently, I wrote the definition, but not the declaration. I need more
sleep.`)

```
-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1

iQIcBAABAgAGBQJYm+mSAAoJECzE45aCeCKZtvQP/AgcBOSra58hDhYiNpOUvDN8
sVADViGSX37Z2xh+NfnIpA8uYPHpO8GN84o8Y4xRqqc7JQPWDC6wm7JG1mwRIFCo
3SGfE8q+zLCj9hZXNCjPUe0ICQ/8pklRY4DYfsKoES59cg94IO9LSKgAkpbh2kxw
YRF9V3SZT+yRER/TSLFvPoi6z0pyHX/FYHtQrKgeh+k9S3y8ScKMmWJI6NFtIIWB
Z+D5GI9KPnTqmLN2OwWAqWq0DKO9es+lGw2BLuKYnds09iBLn9ASdOAIy7FweuEW
qFW51TESuKZ9j0QMOnwgoConEIjHL2lLon0x1OMOaIw3AmvfjR+VEVCHYbNhNG5t
cd8j3ln2nQVWBo2BCwa80KFgqSgsT1hH2PhrSPCQdR0QM6ZCKr0ooJaSMbNcYhV4
vSLKFQiy1us91FwHO/WBkEFyrpOWh+LrtAu5Vt8Tza1y0uVzX2J+kVZdA0Rd8WGn
Zo95GwlUqVAscGJYYsfrs/Hk2VvJhJSV2FGCNgOwizGSXSMAbpaVvwhMwZEu4DxO
II3aWtsMvKwuk1i9UyCtK0UaTILmTmByEHxjfLZPENTsFvpxD4UfB20dfKUU3+1i
JCwfCb/NnT0Q1f9q1voAKaXxVIGIX/ATLvgSOvPJOEU2dFYz7vQfEwCRd46ocoOo
EJfCFufxOyRBZsY+esra
=axyy
-----END PGP SIGNATURE-----
```
