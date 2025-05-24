/* functions.c: ENCM 369 Summer 2024 Lab 3 Exercise A */

/* INSTRUCTIONS:
 *   You are to write a RARS translation of this C program.  Because
 *   this is the first assembly language program you are writing where you
 *   must deal with register conflicts and manage the stack, there are
 *   a lot of hints given in C comments about how to do the translation.
 *   In future lab exercises and on midterms, you will be expected
 *   to do this kind of translation without being given very many hints!
 */

/* Hint: Function prototypes, such as the next two lines of C,
 * are used by a C compiler to do type checking and sometimes type
 * conversions in function calls.  They do NOT cause ANY assembly
 * language code to be generated.
 */

int funcA(int first, int second, int third, int fourth);

int funcB(int y, int z);

int cherry = 0x30000;

int main(void)
{
  /* Hint: This is a nonleaf function, so it needs a stack frame. */

  /* Instruction: Normally you could pick whatever two s-registers you
   * like for apple and banana, but in this exercise you must use s0
   * for apple and s1 for banana.
   */
  int apple;
  int banana;
  apple = 0x700;
  banana = 0x600;
  banana += funcA(3, 5, 6, 4);
  cherry += (banana - apple);

  /* At this point train should have a value of 0x3058f. */

  return 0;
}

int funcA(int first, int second, int third, int fourth)
{
  /* Hint: This is a nonleaf function, so it needs a stack frame,
   * and you will have to make copies of the incoming arguments so
   * that a-registers are free for outgoing arguments. */

  /* Instructions: Normally you would have a lot of freedom within the
   * calling conventions about what s-registers you use, and about where
   * you put copies of incoming arguments, but in this exercise you
   * must copy first to s0, second to s1, third to s2, and fourth to s3, 
   * and use s4 for kiwi, s5 for mango, and s6 for orange.
   */
  int kiwi;
  int mango;
  int orange;
  orange = funcB(second, first);
  kiwi = funcB(fourth, third);
  mango = funcB(third, fourth);

  return kiwi + mango + orange;
}

int funcB(int y, int z)
{
  /* Hint: this is a leaf function, and it shouldn't need to use any
   * s-registers, so you should not have use the stack at all. */
  return y + z * 128;
}
