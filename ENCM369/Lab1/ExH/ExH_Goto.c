#include <stdio.h>

void print_array(const char *str, const int *a, int n);

void sort_array(int *x, int n);

int main(void)
{
	int test_array[] = {4000, 5000, 7000, 1000, 3000, 4000, 2000, 6000};
	
	print_array("before sorting...", test_array, 8);
	sort_array(test_array, 8);
	print_array("after sorting...", test_array, 8);
	return 0;
}

void print_array(const char *str, const int *a, int n)
{
	int i;
	puts(str);
	i = 0;
	for_top:
	if (i == n) goto for_end;
	if (i > n) goto for_end;
	printf("    %d", a[i]);
	i++;
	goto for_top;
	for_end:
	printf("\n");
}

void sort_array(int *x, int n)
{
	int outer, inner, max, i_of_max;
	outer = n - 1;
	for_top_2:
	if (outer == 0) goto for_end_2;
	if (outer < 0) goto for_end_2;
	i_of_max = outer;
	max = x[outer];
	inner = 0;
	inner_loop_top:
	if (inner == outer) goto inner_loop_end;
	if (inner > outer) goto inner_loop_end;
	if (x[inner] == max) goto if_end;
	if (x[inner] < max) goto if_end;
	i_of_max = inner;
	max = x[inner];
	if_end:
	inner++;
	goto inner_loop_top;
	inner_loop_end:
	x[i_of_max] = x[outer];
	x[outer] = max;
	outer--;
	goto for_top_2;
	for_end_2:
	;
}