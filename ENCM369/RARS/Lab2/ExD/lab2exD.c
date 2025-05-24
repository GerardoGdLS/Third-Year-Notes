// lab2exD.c
// ENCM 369 Summer 2024 Lab 2 Exercise D
//
// INSTRUCTIONS
//   Your overall goal is to translate this program into RARS
//   assembly language.  Proceed using the following steps:
//
//   1. Make sure you know what this C program does.  If you're not
//      sure, add calls to printf.
//
//   2. Translate the program to Goto-C.  If you're not sure your
//      translation is correct, add calls to printf. 
//
//   3. Write down a list of local variables and the registers
//      you need for them.  (You will later type this in as
//      a comment in your RARS source code.)   
//
//   4. Using the products of Steps 2 and 3, write a RARS translation
//      of this program, in a file called lab2exD.asm.  Use comments (a)
//      to describe allocation of local variables to s-registers and
//      (b) to explain what each RARS instruction does.
//
//      Your RARS code must closely match the C code.  In particular,
//      the translation of the for loop should include generation of
//      the address of alpha[i] by adding 4 times i to the address of
//      alpha[0], and the translation of the while loop should use
//      pointer arithmetic.
//
//   5. Test your translation using RARS.


int alpha[8] = { 0xb1, 0xe1, 0x91, 0xc1, 0x81, 0xa1, 0xf1, 0xd1 };
int beta[8] = { 0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70 };

int main(void)
{
  int *p;
  int *q;
  int *guard;
  int max, i;

  // Put value of largest element of alpha into max.
  max = alpha[0];
  for (i = 1; i < 8; i++)
    if (alpha[i] > max)
      max = alpha[i];
      
  // Copy elements from beta to alpha in reverse order,
  // writing over the initial values in alpha.
  p = beta;
  q = alpha + 7;
  guard = p + 8;
  while (p != guard) {
    *q = *p;
    p++;
    q--;
  }

  return 0;
}
