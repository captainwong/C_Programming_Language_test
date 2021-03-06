#include <stdio.h>
/*
当fahr = 0, 20, 30, ..., 300时，
分别打印华氏温度与摄氏温度对照表;
浮点数版本
*/
main()
{
	/* while
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = (float)lower;
	printf("当fahr = 0, 20, 30, ..., 300时，\n\
分别打印华氏温度与摄氏温度对照表;\n\
浮点数版本\n");
	printf("fahr\tcelsius\n");
	while(fahr <= upper)
	{
		celsius = (5.0f / 9.0f) * (fahr - 32.0f);
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr += step;
	}
	*/

	// for 逆序
	/*
	当fahr = 300, 280, 260, ..., 0时，分别
	打印华氏温度与摄氏温度对照表;
	浮点数版本
	*/
	float fahr = 300.0;
	printf("当fahr = 300, 280, 260, ..., 0时，分别\n\
打印华氏温度与摄氏温度对照表;\n\
浮点数版本\n");
	printf("fahr\tcelsius\n");
	for(; fahr >= 0.0; fahr -= 20.0)
	{
		printf("%3.0f\t%6.1f\n", fahr, (5.0f / 9.0f) * (fahr - 32.0f));
	}
}