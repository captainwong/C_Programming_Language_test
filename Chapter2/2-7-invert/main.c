/*
* Write a function invert(x,p,n) that returns x with the n bits that begin at position p
* inverted (i.i., 1 changed to 0 and vice versa), leaving the other bits unchanged.
*/

#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n)
{
	return x ^ (~(~0U << n) << p);
}

void printbits(unsigned int val)
{
	int count = 0;
	for (size_t i = sizeof(val) * 8; i > 0; i--) {
		if ((1U << (i - 1)) & val) {
			printf("1");
		} else {
			printf("0");
		}
		if (i != 1 && ++count % 8 == 0) {
			printf(" ");
		}
	}
}

int main()
{
	for (unsigned int x = 0; x < 700; x += 49) {
		for (int n = 1; n < 8; n++) {
			for (int p = 1; p < 8; p++) {
				unsigned int y = invert(x, p, n);
				printf("invert(%u, %d, %d) = %u\n", x, p, n, y);
				printf("invert("); printbits(x); printf(", %d, %d) = ", p, n); printbits(y); printf("\n");
			}
		}
	}
}
