#include <stdio.h>
#include <stdlib.h>
/*
*/
int max;
main()
{
	/*
	int c;
	while((c = getchar()) != EOF)
		putchar(c);
	//printf("%d\n", EOF); 
	*/

	
	double nc;
	max = 0;
	//int i = max;
	for(nc = 0; getchar() != EOF; ++nc)
		;
	printf("%.0f\n", nc);
	system("pause");
}