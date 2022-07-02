#include <stdio.h>

#define TAB_SIZE 4

int main()
{
	int tab_size = TAB_SIZE;
	int c, l = 0, j;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			j = tab_size - (l % tab_size);
			for (int i = 0; i < j; i++) {
				putchar(' ');
				l++;
			}
		} else if (c == '\n') {
			putchar(c);
			l = 0;
		} else {
			putchar(c);
			l++;
		}
	}
	return 0;
}
