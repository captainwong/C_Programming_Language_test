#include <stdio.h>
/*
��fahr = 0, 20, 30, ..., 300ʱ��
�ֱ��ӡ�����¶��������¶ȶ��ձ�;
�������汾
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
	printf("��fahr = 0, 20, 30, ..., 300ʱ��\n\
�ֱ��ӡ�����¶��������¶ȶ��ձ�;\n\
�������汾\n");
	printf("fahr\tcelsius\n");
	while(fahr <= upper)
	{
		celsius = (5.0f / 9.0f) * (fahr - 32.0f);
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr += step;
	}
	*/

	// for ����
	/*
	��fahr = 300, 280, 260, ..., 0ʱ���ֱ�
	��ӡ�����¶��������¶ȶ��ձ�;
	�������汾
	*/
	float fahr = 300.0;
	printf("��fahr = 300, 280, 260, ..., 0ʱ���ֱ�\n\
��ӡ�����¶��������¶ȶ��ձ�;\n\
�������汾\n");
	printf("fahr\tcelsius\n");
	for(; fahr >= 0.0; fahr -= 20.0)
	{
		printf("%3.0f\t%6.1f\n", fahr, (5.0f / 9.0f) * (fahr - 32.0f));
	}
}