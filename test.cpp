#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <printf.h>
#include <stdarg.h>
#include "snippets.h"
#include "snippets.cpp"

typedef struct Array {
	// DATA
	size_t length;
	size_t size;
	size_t typeSize;
	char* contents;

	// FUNCTIONS
	size_t len () {
		return length;
	}
	
	Array (int* _contents, size_t _length) {
		typeSize = sizeof (int);
		length = _length;
		size = length * typeSize;
		size_t _contentsTransferSize = (_length * typeSize / sizeof (char));
		char* _contentsTransfer = (char*) _contents;
		contents = (char*) malloc (_contentsTransferSize);
		for (int i = 0; i < _contentsTransferSize; ++i) {
			contents[i] = _contentsTransfer[i];
		}
	}
	Array (int* _contents, size_t _length, size_t _typeSize) {
		typeSize = _typeSize;
		length = _length;
		size = length * typeSize;
		size_t _contentsTransferSize = (_length * typeSize / sizeof (char));
		char* _contentsTransfer = (char*) _contents;
		contents = (char*) malloc (_contentsTransferSize);
		for (int i = 0; i < _contentsTransferSize; ++i) {
			contents[i] = _contentsTransfer[i];
		}
	}
	Array (void* _contents, size_t _length, size_t _typeSize) {
		typeSize = _typeSize;
		length = _length;
		size = length * typeSize;
		size_t _contentsTransferSize = (_length * typeSize / sizeof (char));
		char* _contentsTransfer = (char*) _contents;
		contents = (char*) malloc (_contentsTransferSize);
		for (int i = 0; i < _contentsTransferSize; ++i) {
			contents[i] = _contentsTransfer[i];
		}
	}

	void print () {
		printf ("{");
		for (uint64 i = 0; i < (length * typeSize); i += typeSize) {
			char c = (i < size - typeSize) ? ',' : '\0';
			printf ("%d%c", (int)(contents[i]), c);
		}
		printf ("}");
	}
} Array;

int main (int argc, char** argv, char** env) {
	int x[] = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5};
	printf ("x is %lu in size, %lu in length.\n\n", sizeof (x), sizeof (x) / sizeof (int));

	Array y (x,(sizeof(x)/sizeof(x[0])));
	printf ("y = ");
	y.print();
	printf ("\n");
	//printf ("x contents 1 = %d\n", y.contents[sizeof(int)]);

	return 0;
}
