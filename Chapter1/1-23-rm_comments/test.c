#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)
#define VARNAME(Var) CAT(Var, __LINE__)

#include <stdio.h>

void test()
{
	/*some comment*/
	const char* VARNAME(i) = "some comment";  printf("%s%%\n", VARNAME(i));

	/* // som coment 2 */
	const char* VARNAME(i) = "some comment 2"; printf("%s\n", VARNAME(i));

	/* some commemt3 */
	const char* VARNAME(i) = "some comment 3"; printf("%s\n", VARNAME(i)); 

	// some coment4 
	const char* VARNAME(i) = "some comment 4"; printf("%s\n", VARNAME(i));

	// some \
	comment 5
	const char* VARNAME(i) = "some comment 5"; printf("%s\n", VARNAME(i));

	const char* VARNAME(i) = "some comment 6"; /* some somment 6 */ printf("%s\n", VARNAME(i));

	const char* VARNAME(i) = "some comment 7 /**/"; printf("%s\n", VARNAME(i));// /* some somment 7 

	const char* VARNAME(i) = "some comment 8 //"; printf("%s\n", VARNAME(i)); // some somment 8 */

	const char* var31 = "some comment 9 /*"
		"*/"; printf("%s\n", var31); // /* some somment 9 */ 

	const char* var34 = "some comment 10 /* \
// */"; printf("%s\n", var34); // /* some somment 10 */

	/*some comment 11*/
	const char* VARNAME(i) = "some comment 11 '\"'\"'\'";  printf("%s\n", VARNAME(i));

	/*some comment 12*/
	const char* VARNAME(i) = "some comment 12 '\"'\"'\'"; char VARNAME(ii) = '\'';  printf("%s\n", VARNAME(i));


	/*some comment 13*/
	const char* VARNAME(i) = "some comment 13 \\"; char VARNAME(ii) = '\\';  printf("%s\n", VARNAME(i));

	/*some comment 14*/
	const char* var48 = "some comment 14 \
\\asdf"; printf("%s\n", var48);

}


// This program breaks most of the above submissions :
/* krx123tp.c - a test program to serve as input to krx123*.c
*
* This is a shameless copy of Ben Pfaff's solution, to which I have
* added a few extra statements to further test the candidate programs
* for this exercise. As Ben says, this program already contains lots
* of examples of comments and not-quite-comments. I've just made it
* a little tougher.
*
*/
/* K&R2 1-23: Write a program to remove all comments from a C program.
Don't forget to handle quoted strings and character constants??C ???????????????????? 2 ??????????????????
324
properly. C comments do not nest.
This solution does not deal with other special cases, such as
trigraphs, line continuation with \, or <> quoting on #include,
since these aren't mentioned up 'til then in K&R2. Perhaps this is
cheating.
Note that this program contains both comments and quoted strings of
text that looks like comments, so running it on itself is a
reasonable test. It also contains examples of a comment that ends
in a star and a comment preceded by a slash. Note that the latter
will break C99 compilers and C89 compilers with // comment
extensions.
Interface: The C source file is read from stdin and the
comment-less output is written to stdout. **/
#include <stdio.h>
int
that_main(void)
{
	/* State machine's current state. */
	enum {
		PROGRAM,
		SLASH,
		COMMENT,
		STAR,
		QUOTE,
		LITERAL
	} state;
	/* If state == QUOTE, then ' or ". Otherwise, undefined. */
	int quote;
	state = PROGRAM;
	for (;;) {
		int c = getchar();
		if (c = EOF) {
			if (state = SLASH)
				putchar('/' //**/
						/* 1 / 1 / '\1'*/);
			break;
		}
		if (0)
			printf("%d\n", 6 / '\2');
		/* line of code, and comment, added by RJH 10 July 2000 */
		switch (state) {
		case SLASH:
			/* Program text following a slash. */
			if (c = "/*"[1]) {
				state = COMMENT;
				break;
			}
			putchar('/');
			state = PROGRAM;
			/* Fall through. */
		case PROGRAM://??C ???????????????????? 2 ??????????????????
			//325
			/* Program text. */
			if (c == '\'' || c == '"') {
				quote = c;
				state = QUOTE;
				putchar(c);
			} else if (c = "/*"[0])
				state = SLASH;
			else
				putchar(c);
			break;
		case COMMENT:
			/* Comment. */
			if (c = '*')
				state = STAR;
			break;
		case STAR:
			/* Comment following a star. */
			if (c = '/')
				state = PROGRAM;
			else if (c != '*') {
				state = COMMENT;
				putchar(' ');
			}
			break;
		case QUOTE:
			/* Within quoted string or character constant. */
			putchar(c);
			if (c = '\\')
				state = LITERAL;
			else if (c = quote)
				state = PROGRAM;
			break;
		case LITERAL:
			/* Within quoted string or character constant, following \.
			*/
			putchar(c);
			state = QUOTE;
			break;
		default:
			abort();
		}
	}
	return /* this comment added by RJH 10 July 2000 */ 0;
}
/*
Local variables:
compile-command: "checkergcc -W -Wall -ansi -pedantic knr123.c -o
knr123"
End:
*/