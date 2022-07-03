#include <stdio.h>

#define MAX_WORD_LEN 10

int digitlen(int digit)
{
	int len = 0;
	while (digit) {
		len++;
		digit /= 10;
	}
	return len;
}

int main()
{
	int freq[MAX_WORD_LEN + 1] = { 0 };
	int c, len = 0, maxfreq = 0, dlen = 0;
	char fmt[128] = { 0 };

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
			if (len > 0) {
				freq[len - 1]++;
				if (freq[len - 1] > maxfreq) {
					maxfreq = freq[len - 1];
				}
				len = 0;
			}
		} else {
			if (len == MAX_WORD_LEN) {
				freq[MAX_WORD_LEN]++;
				if (freq[MAX_WORD_LEN] > maxfreq) {
					maxfreq = freq[MAX_WORD_LEN];
				}
			} else {
				len++;
			}
		}
	}

	dlen = digitlen(maxfreq);
	snprintf(fmt, sizeof(fmt), "%%-%dd", dlen);

	for (int i = maxfreq; i > 0; i--) {
		printf(fmt, i);
		printf(" |");
		for (int j = 0; j < MAX_WORD_LEN + 1; j++) {
			if (freq[j] >= i) {
				printf(" * ");
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}

	for (int i = 0; i < dlen; i++) {
		printf(" ");
	}
	printf(" +");
	for (int i = 0; i < MAX_WORD_LEN + 1; i++) {
		printf("---");
	}
	printf("\n");

	for (int i = 0; i < dlen; i++) {
		printf(" ");
	}
	printf(" ");
	for (int i = 0; i < MAX_WORD_LEN; i++) {
		printf("%3d", i + 1);
	}
	printf(" >10\n");

	return 0;
}
