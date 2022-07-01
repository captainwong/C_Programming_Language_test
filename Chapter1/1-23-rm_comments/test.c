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

}