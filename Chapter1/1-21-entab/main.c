#include <stdio.h>

#define TAB_SIZE 4
#define LINE_SIZE 1024

int main()
{
	int c, l = 0, spacing = 0, spaces = 0, tab_size = TAB_SIZE;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (spacing) {
				if (++spaces == TAB_SIZE) {
					putchar('\t');
					spacing = 0;
					spaces = 0;
				}
			} else if (l % tab_size == 0) {
				spacing = 1;
				spaces = 1;
			} else {
				putchar(' ');
			}
			l++;
		} else {
			if (spacing) {
				for (int i = 0; i < spaces; i++) {
					putchar(' ');
				}
				spacing = 0;
				spaces = 0;
			}

			putchar(c);
			l++;

			if (c == '\n') {
				l = 0;
			}
		}
	}

	return 0;
}
