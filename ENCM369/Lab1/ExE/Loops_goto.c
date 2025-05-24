#include <stdio.h>
int main(void)
{
	int a[4] = {1200, 3400, 5600, 7800};
	int *p = a;
	int i;
	for_loop_top:
	if (p > a+3) goto for_loop_end;
	printf("%d\n", *p);
	p += 1;
	goto for_loop_top;
	for_loop_end:
	i = 234567;
	while_top:
	if (i < 2) goto while_end;
	printf("%d\n", i);
	i /= 16;
	goto while_top;
	while_end:
	return 0;
}