// lab03exC.c: ENCM 369 Summer 2024 Lab 3 Exercise C

// INSTRUCTIONS:
//   You are to write a RARS translation of this C program, compatible
//   with all of the calling conventions presented so far in ENCM 369.

int sat(int x, int b);

int sum_of_sats(const int *a, int n, int max_mag);

int aaa[] = { 11, 11, 3, -11};
int bbb[] = { 200, -300, 400, 500 };
int ccc[] = { -2, -3, 2, 1, 2, 3 };

int main(void)
{
    // Normally you could pick whatever s-registers you like for alpha,
    // beta, and gamma.  However in this exercise you should use s0
    // for alpha, s1 for beta, and s2 for gamma -- this will help
    // make sure you learn to manage s-registers correctly.
    
    int alpha, beta, gamma;
    gamma = 2000;
    alpha = sum_of_sats(aaa, 4, 9);
    beta = sum_of_sats(bbb, 4, 250);
    gamma += sum_of_sats(ccc, 6, 2) + alpha + beta;

    // Here gamma should have a value of 2465.

    return 0;
}

int sat(int x, int b)
{
    // Note: Even though this function has multiple return statements,
    // you should code it in assembly language with only one jr ra
    // instruction at the end of the function definition.

    // Hint: Something like sub t0, zero, a1 might be useful somewhere.

    if (x > b)
        return b;
    else if (x < -b)
        return -b;
    return x;
}

int sum_of_sats(const int *a, int n, int max_mag)
{
    // Normally you could pick whatever s-registers you like for a, n,
    // max_mag, i, and result.  However in this exercise you should use s0
    // for a, s1 for n, s2 for max_mag, s3 for i, and s4 for result; 
    // this will help make sure you manage s-registers correctly.

    int i;
    int result;
    result = 0;
    for (i = 0; i < n; i++)
      result += sat(a[i], max_mag);
    return result;
}
