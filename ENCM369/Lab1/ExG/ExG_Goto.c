#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ABS_F (5.0e-9)
#define POLY_DEGREE 4

double polyval(const double *a, int n, double x);
/*Return a[0] + a[1] * x ... a[n] * pow(x,n).*/

int main(void)
{
	double f[] = {1.47, 0.73, -2.97, -1.15, 1.00};
	double dfdx[POLY_DEGREE];
	
	double guess;
	int max_updates;
	int update_count;
	int n_scanned;
	int i;
	int flag;
	
	double current_x, current_f, current_dfdx;
	
	printf("This program demonstrates use of Newton's Method to find\n""appropriate roots of the polynomial\nf(x)= ");
	printf("%.2f", f[0]);
	
	i = 1;
	outer_top:
	if (i > POLY_DEGREE) goto outer_end;
	if (f[i] < 0) goto negative;
	printf("+ %.2f*pow(x,%d)", f[i], i);
	goto inner_end;
	negative:
	printf("- %.2f*pow(x,%d)", -f[i], i);
	inner_end:
	i++;
	goto outer_top;
	outer_end:
	printf("\nPlease enter a guess at a root, and a maximum number of\n" "updates to do, separated by a space.\n");
	n_scanned = scanf("%lf%d", &guess, &max_updates);
	if (n_scanned == 2) goto check_updates;
	printf("Sorry, I couldn't understand the input.\n");
	exit(1);
	check_updates:
	if (max_updates > 0) goto evaluate;
	printf("Sorry, I must be allowed do at least one update.\n");
	exit(1);
	evaluate:
	printf("Running with initial guess %f.\n", guess);
	i = POLY_DEGREE - 1;
	eval_top:
	if (i < 0) goto eval_end;
	dfdx[i] = (i + 1)*f[i+1]; //Calculus!
	i--;
	goto eval_top;
	eval_end:
	current_x = guess;
	update_count = 0;
	flag = 0;
	while_top:
	if (flag != 0) goto while_end;
	current_f = polyval(f, POLY_DEGREE, current_x);
	printf("%d update(s) done; x is %.15f; f(x) is %.15e\n", update_count, current_x, current_f);
	if (fabs(current_f) > MAX_ABS_F) goto flag_2;
	if (fabs(current_f) == MAX_ABS_F) goto flag_2;
	flag = 1;
	goto check_flag;
	flag_2:
	if (update_count != max_updates) goto check_flag;
	flag = 2;
	check_flag:
	if (flag) goto while_top;
	current_dfdx = polyval(dfdx, POLY_DEGREE - 1, current_x);
	current_x -= current_f/current_dfdx;
	update_count++;
	goto while_top;
	while_end:
	if (flag != 2) goto not_two;
	printf("%d updates performed, |f(x)| still >= %g.\n", update_count, MAX_ABS_F);
	goto end_run;
	not_two:
	printf("Stopped with approximate solution of %.10f.\n", current_x);
	end_run:
	return 0;
}

double polyval(const double *a, int n, double x)
{
	double result = a[n];
	int i;
	i = n - 1;
	for_loop_top:
	if (i < 0) goto for_loop_end;
	result *= x;
	result += a[i];
	i--;
	goto for_loop_top;
	for_loop_end:
	return result;
}