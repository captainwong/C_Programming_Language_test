/*
* Write a program to "fold" long input lines into two or more shorter lines after
* the last non-blank character that occurs before the n-th column of input.
* Make sure your program does something intelligent with very long lines, and if
* there are no blanks or tabs before the specified column.
*/


#include <stdio.h>
#include <string.h>

#define FOLD_LENGTH 80
#define TAB_SIZE 4

int main()
{
	char line[FOLD_LENGTH + 1];
	int c, l = 0, last_blank = 0;
	while ((c = getchar()) != EOF) {
		if (l < FOLD_LENGTH) {
			line[l++] = c;
			if (c == ' ') {
				last_blank = l - 1;
			} else if (c == '\n') {
				line[l - 1] = '\0';
				printf("%s\n", line);
				l = 0;
				last_blank = 0;
			} else if (c == '\t') {
				l--;
				int tsize = (TAB_SIZE - (l % TAB_SIZE));
				if (FOLD_LENGTH - l > tsize) {
					l += tsize;
				} else {
					line[l] = '\0';
					printf("%s\n", line);
					l = 0;
					last_blank = 0;
				}
			}
		} else {
			if (last_blank > 0) {
				line[last_blank] = '\0';
				printf("%s\n", line);
				l = FOLD_LENGTH - last_blank - 1;
				memmove(line, line + last_blank + 1, l);
				last_blank = 0;
			} else {
				line[l] = '\0';
				printf("%s\n", line);
				l = 0;
				last_blank = 0;
			}			
		}
	}
}
