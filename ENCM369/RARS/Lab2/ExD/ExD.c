#include <stdio.h>

int alpha[8] = {0xb1, 0xe1, 0x91, 0xc1, 0x81, 0xa1, 0xf1, 0xd1};
int beta[8] = {0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70};

int main(void)
{
	int *p;
	int *q;
	int *guard;
	int max, i;
	
	max = alpha[0];
	i = 1;
	L1:
	if (i == 8) goto L2;
	if (i > 8) goto L2;
	if (alpha[i] > max) goto L3;
	i++;
	goto L1;
	
	L3:
	max = alpha[i];
	i++;
	goto L1;
	
	L2:
	p = beta;
	q = alpha + 7;
	guard = p + 8;
	
	L4:
	if (p == guard) goto L5;
	*q = *p;
	p++;
	q--;
	goto L4;
	
	L5:
	return 0;
}