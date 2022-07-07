/*
* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right
* by n bit position.
*/

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n)
{
	n %= sizeof(x) * 8;
	for (int i = 0; i < n; i++) {
		x = (x >> 1) | ((x & 1) << (sizeof(x) * 8 - 1));
	}
	return x;
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
		for (int n = 1; n < 32; n++) {
			unsigned int y = rightrot(x, n);
			printf("rightrot(%u, %d) = %u\n", x, n, y);
			printf("rightrot("); printbits(x); printf(", %d) = ", n); printbits(y); printf("\n");
		}
	}
}
