#include <stdio.h>

int main(void)
{
	int arg = 30;
	printf("func1 called with arg1 = %d.\n", arg);
	if (arg > 14) goto gt_15;
	printf("At least one of func2(%d) or func3(%d) is true.\n\n", arg, arg);
	goto end;
	gt_15:
	printf("func2 called with arg2 = %d.\n", arg);
	if (arg > 24) goto neither;
	printf("At least one of func2(%d) or func3(%d) is true.\n\n", arg, arg);
	goto end;
	neither:
	printf("func3 called with arg3 = %d.\n", arg);
	printf("Neither func2(%d) nor func3(%d) is true.\n\n", arg, arg);
	end:
	return 0;
}