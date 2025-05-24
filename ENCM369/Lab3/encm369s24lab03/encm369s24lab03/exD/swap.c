/*
 * swap.c
 * ENCM 369 Summer 2024 Lab 3 Exercise D
 */


/* INSTRUCTIONS:
 *   A partially-completed assembly language translation of this
 *   file can be found in swap.asm.  Complete the translation
 *   by adding the necessary instructions to main and swap in
 *   swap.asm.
 */

void swap(int *p, int *q);
/* REQUIRES:
 *   p and q point to variables
 * PROMISES:
 *   *p == value of *q on entry to swap.
 *   *q == value of *p on entry to swap.
 */

int foo[] =  {0x700, 0x600, 0x500, 0x400, 0x300, 0x200, 0x100};

int main(void)
{
  /* These three swaps will reverse the order of the elements
   * in the array foo. */
  swap(&foo[0], &foo[6]);
  swap(&foo[1], &foo[5]);
  swap(&foo[2], &foo[4]);

  return 0;
}

void swap(int *p, int *q)
{
  /* Hint: Think carefully about when use of the C * operator
   * means "load" and when it means "store".
   */
  int old_star_q;

  old_star_q = *q;
  *q = *p;
  *p = old_star_q;
}
