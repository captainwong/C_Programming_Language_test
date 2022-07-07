/*
* Write a function 'setbits(x,p,n,y) that returns x with the n bits that begin at position p
* set to the rightmost n bits of y, leaving the other bits unchanged.
*/

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	return ((~(~0U << n) & y) << (p + 1 - n)) | (x & ((~0U << (p + 1)) | ~(~0U << (p + 1 - n))));
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
	for (unsigned int x = 0; x < 30000; x += 511) {
		for (unsigned int y = 0; y < 1000; y += 37) {
			for (int p = 1; p < 16; p++) {
				for (int n = 1; n <= p + 1; n++) {
					unsigned int k = setbits(x, p, n, y);
					printf("setbits(%u, %d, %d, %u) = %u\n", x, p, n, y, k);
					printf("setbits("); printbits(x); printf(", %d, %d, ", p, n); printbits(y); printf(") = "); printbits(k); printf("\n");
				}
			}
		}
	}
	return 0;
}
