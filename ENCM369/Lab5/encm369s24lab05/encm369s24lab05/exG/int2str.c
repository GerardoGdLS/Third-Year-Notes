// int2str.c
// ENCM 369 Summer 2024 Lab 5 Exercise G

#include <stdio.h>

char digits[] = "0123456789";

void int2str(char *dest, int src)
{
  unsigned abs_src, ten, rem, temp;
  char *p, *q;

  if (src == 0) {
    dest[0] = '0';
    dest[1] = '\0';
    return;
  }

  if (src == -2147483648)  // check for 32-bit "weird number"
    abs_src = 0x80000000u;
  else if (src < 0)
    abs_src = -src;
  else
    abs_src = src;

  // compute and store decimal digits of abs_src
  p = dest;
  ten = 10u;
  while (abs_src != 0) {
    rem = abs_src % ten;
    *p = digits[rem];
    p++;
    abs_src /= ten;
  }

  // store '-' if necessary, then terminate string
  if (src < 0) {
    *p = '-';
    p++;
  }
  *p = '\0';

  // reverse order of chars in string
  q = p - 1;
  p = dest;
  while (p < q) {
    temp = *p;
    *p = *q;
    *q = temp;
    p++;
    q--;
  }
}

char buf[12];
char finish[] = "\"\n";

void try_it(const char *msg, int src)
{
  int2str(buf, src);
  fputs(msg, stdout);
  fputs(buf, stdout);
  fputs(finish, stdout);
}

int main(void)
{
  try_it("try #1: \"", 0);
  try_it("try #2: \"", 1);
  try_it("try #3: \"", -1);
  try_it("try #4: \"", -2147483648);
  try_it("try #5: \"", -2147483647);
  try_it("try #6: \"", 2147483647);
  try_it("try #7: \"", 123);
  try_it("try #8: \"", -456789);
  return 0;
}





    .text
    .globl  int2str
int2str:
    # Handle special case for 0
    beq     a1, zero, L0
    # Handle special case for -2147483648
    li      t6, 0x80000000
    bne     a1, t6, L1
    li      t0, 0x80000000
    j       L2

L1:
    # Handle negative numbers
    bge     a1, zero, L3
    sub     t0, zero, a1
    li      a4, 45                # ASCII '-' for negative numbers
    sb      a4, 0(a0)             # Store '-' at the start
    addi    a0, a0, 1             # Move destination pointer
    j       L4

L3:
    mv      t0, a1                # Non-negative numbers

L2:
    mv      t4, a0                # Store destination pointer
    li      t1, 10                # Divisor for extracting digits

L4:
    # Convert integer to string
    beq     t0, zero, L5
L6:
    rem     t2, t0, t1           # Get remainder (last digit)
    la      a2, digits
    add     a2, a2, t2           # Address of the character for the digit
    lb      a3, 0(a2)
    sb      a3, 0(t4)            # Store digit in buffer
    addi    t4, t4, 1            # Move buffer pointer
    div     t0, t0, t1           # Remove last digit from number
    j       L6

L5:
    # Add null terminator
    sb      zero, 0(t4)

    # Reverse the string
    subi    t4, t4, 1            # Move to the last character
    mv      t5, a0               # Save start pointer
    beq     t5, t4, L7          # If only one character, skip reversal
L8:
    lb      t2, 0(t5)           # Load character from start
    lb      t3, 0(t4)           # Load character from end
    sb      t3, 0(t5)           # Swap characters
    sb      t2, 0(t4)
    addi    t5, t5, 1           # Move pointers
    addi    t4, t4, -1
    blt     t5, t4, L8         # Continue if pointers haven't met

L7:
    jr      ra

L0:
    # Special case for zero
    li      t6, 48              # ASCII '0'
    sb      t6, 0(a0)
    sb      zero, 1(a0)         # Null terminate
    jr      ra












	.text
	.globl	int2str
int2str:
	bne	a1, zero, L2
	li	t6, 48
	sb	t6, (a0)
	li	t6, 0
	sb	t6, 1(a0)
	j	L10
	
L2:
	li	t6, 0x80000000
	bne	a1, t6, L3
	li	t0, 0x80000000
	j	L5
L3:
	bge	a1, zero, L4
	sub	t6, zero, a1
	mv	t0, t6
	j	L5
L4:
	mv	t0, a1
L5:
	mv	t4, a0
	li	t1, 10
L6:
	beq	t0, zero, L7
	rem	t2, t0, t1
	la	a2, digits
	add	a2, a2, t2
	lb	a3, (a2)
	sb	a3, (t4)
	addi	t4, t4, 1
	div	t0, t0, t1
	j	L6
L7:
	bge	a1, zero, L8
	li	a4, 0x2d
	sb	a4, (t4)
	addi	t4, t4, 1
L8:
	li	a4, 0
	sb	a4, (t4)
	addi	t5, t4, -1
	mv	t4, a0
L9:
	bge	t4, t5, L10
	lb	t3, (t4)
	lb	a5, (t5)
	sb	a5, (t4)
	mv	a6, t3
	sb	a6, (t5)
	addi	t4, t4, 1
	addi	t5, t5, -1
	j	L9
L10:
	sb	zero, (a0)	
	jr	ra
