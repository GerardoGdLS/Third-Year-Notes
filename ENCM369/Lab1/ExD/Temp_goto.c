#include <stdio.h>
int main(void)
{
	int celsius_temp = 0;
	if (celsius_temp < 27) goto lt_27;
	printf("The temperature is a warm %d degrees.\n", celsius_temp);
	printf("Have a glass of water.\n");
	goto end;
	lt_27:
	if (celsius_temp < 15) goto lt_15;
	printf("The temperature is a pleasant %d degrees.\n", celsius_temp);
	printf("Have a nice day.\n");
	goto end;
	lt_15:
	if (celsius_temp < 1) goto lt_1;
	printf("The temperature is a cool %d degrees.\n", celsius_temp);
	printf("Wear a jacket.\n");
	goto end;
	lt_1:
	printf("The weather is a chilly %d degrees.\n", celsius_temp);
	printf("Don't slip on the ice.\n");
	end:
	return 0;
}
	