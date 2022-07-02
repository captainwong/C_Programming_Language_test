#ifdef _MSC_VER 
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>

// 统计输入文件中的行数、单词数、字符数
// 结果写入fout
void wc(FILE* f, FILE* fout)
{
	int c, nl, nw, nc, is_space;
	nl = nw = nc = is_space = 0;
	while ((c = fgetc(f)) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			is_space = 1;
		else if (is_space) {
			++nw;
			is_space = 0;
		}
	}
	fprintf(fout, "%d %d %d\n", nl, nw, nc);
}

void gen()
{
	const char* ws = " \f\t\v";
	const char* al = "abcdefghijklmnopqrstuvwxyz";
	const char* i5 = 
		"a b c d e f g h i j k l m "
		"n o p q r s t u v w x y z "
		"a b c d e f g h i j k l m "
		"n o p q r s t u v w x y z "
		"a b c d e f g h i j k l m "
		"n\n";

	FILE* f;
	
	// 0. input file contanis 0 words
	f = fopen("test0", "w");
	assert(f);
	fclose(f);

	// 1. input file contains 1 enormous word without any newlines
	f = fopen("test1", "w");
	assert(f);
	for (int i = 0; i < 66000 / 26 + 1; i++) {
		fputs(al, f);
	}
	fclose(f);

	// 2. input file contains all white space without newlines
	f = fopen("test2", "w");
	assert(f);
	for (int i = 0; i < 66000 / 4 + 1; i++) {
		fputs(ws, f);
	}
	fclose(f);

	// 3. input file contains 66000 newlines
	f = fopen("test3", "w");
	assert(f);
	for (int i = 0; i < 66000; i++) {
		fputc('\n', f);
	}
	fclose(f);

	/*
	* 4. input file contains word/
	*	{huge sequence of whitespaces of different kinds}
	*	/word
	*/
	f = fopen("test4", "w");
	assert(f);
	fputs("word", f);
	for (int i = 0; i < 66000 / 26 + 1; i++) {
		fputs(ws, f);
	}
	fputs("word", f);
	fclose(f);

	// 5. input file contains 66000 single letter words, 66 to the line
	f = fopen("test5", "w");
	assert(f);
	for (int i = 0; i < 1000; i++) {
		fputs(i5, f);
	}
	fclose(f);

	// 6. input file contains 66000 words without any newlines
	f = fopen("test6", "w");
	assert(f);
	for (int i = 0; i < 66000; i++) {
		fputs("word ", f);
	}
	fclose(f);
}

int main(int argc, char** argv)
{
	if (argc == 1) {
		wc(stdin, stdout);
	} else if (argc == 2 && !strcmp(argv[1], "gen")) {
		gen();
	}
	
	return 0;
}
