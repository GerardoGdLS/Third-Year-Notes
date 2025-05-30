// simple_loops1E.c
// ENCM 369 Summer 2024 Lab 1 Exercise E

// INSTRUCTIONS:
//   Recode the definition of main in Goto-C
//   Make sure your modified program produces exactly the same
//   output as the original.

#include <stdio.h>

int main(void)
{
  int a[4] = {1200, 3400, 5600, 7800};
  int *p;
  int i;
  for (p = a; p < a + 4; p++)
    printf("%d\n", *p);
  i = 234567;
  while (i > 1) {
    printf("%d\n", i);
    i /= 16;
  }
  return 0;
}
