# int2str.asm
# ENCM 369 Summer 2024 Lab 5 Exercise G

# BEGINNING of start-up & clean-up code.  Do NOT edit this code.
	.data
exit_msg_1:
	.asciz	"***About to exit. main returned "
exit_msg_2:
	.asciz	".***\n"
main_rv:
	.word	0
	
	.text
	# adjust sp, then call main
	andi	sp, sp, -32		# round sp down to multiple of 32
	jal	main
	
	# when main is done, print its return value, then halt the program
	sw	a0, main_rv, t0	
	la	a0, exit_msg_1
	li      a7, 4
	ecall
	lw	a0, main_rv
	li	a7, 1
	ecall
	la	a0, exit_msg_2
	li	a7, 4
	ecall
        lw      a0, main_rv
	addi	a7, zero, 93	# call for program exit with exit status that is in a0
	ecall
# END of start-up & clean-up code.

	.data
	.globl	digits
digits: .asciz	"0123456789"		# char digits[] = "0123456789"
			
			
# void int2str(char *dest, int str)
#     arg/var	   	GPR
#       dest		 a0
#	src		 a1
#       unsigned abs_src t0
#	unsigned ten	 t1
#	unsigned rem	 t2
#	unsigned temp 	 t3
#	char *p		 t4
#       char *q		 t5
#
# Remark: We have used up all but one of the t-registers.
# However, a2-a7 can also be used for intermediate results.
#
	.text
	.globl	int2str
int2str:
	bne	a1, zero, L2
	li	t6, 48
	sb	t6, (a0)
	sb      zero, 1(a0)         
	j	L10
	
L2:
	li	t6, 0x80000000
	bne	a1, t6, L3
	sub	t0, zero, t6
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
	remu	t2, t0, t1
	la	a2, digits
	add	a2, a2, t2
	lb	a3, (a2)
	sb	a3, (t4)
	addi	t4, t4, 1
	divu	t0, t0, t1
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
	jr	ra
	

	.data
	.globl	buf
buf:	.space	12			# char buf[12]; 
	.globl	finish
finish: .asciz 	"\"\n"			# char finish[] = "\"\n"


# void try_it(const char *msg, int src) 
#
	.text
	.globl	try_it
try_it:
	addi	sp, sp, -32
	sw	ra, 4(sp)
	sw	s0, 0(sp)
	mv	s0, a0			# save msg to s0
	
	la	a0, buf			# a0 = buf
	jal	int2str			# note a1 = src already
	
	mv	a0, s0			# a0 = msg
	li	a7, 4			# service = PrintString
	ecall
	la	a0, buf			# a0 = buf
	li	a7, 4
	ecall
	la	a0, finish		# a0 = finish
	li	a7, 4
	ecall
	
	lw	s0, 0(sp)
	lw	ra, 4(sp)
	addi	sp, sp, 32
	jr	ra	

		
	.data
try1:	.asciz 	"try #1: \""
try2:	.asciz 	"try #2: \""
try3:	.asciz 	"try #3: \""
try4:	.asciz 	"try #4: \""
try5:	.asciz 	"try #5: \""
try6:	.asciz 	"try #6: \""
try7:	.asciz 	"try #7: \""
try8:	.asciz 	"try #8: \""
		
# int main(void)
# 
	.text
	.globl	main
main:
	addi	sp, sp, -32
	sw	ra, 0(sp)
	
	la	a0, try1
	li	a1, 0
	jal	try_it

	la	a0, try2
	li	a1, 1
	jal	try_it

	la	a0, try3
	li	a1, -1
	jal	try_it

	la	a0, try4
	li	a1, -2147483648
	jal	try_it

 	la	a0, try5
	li	a1, -2147483647
	jal	try_it

	la	a0, try6
	li	a1, 2147483647
	jal	try_it

	la	a0, try7
	li	a1, 123
	jal	try_it

	la	a0, try8
	li	a1, -456789
	jal	try_it

	mv	a0, zero	# r.v. = 0

	lw	ra, 0(sp)
	addi	sp, sp, 32
	jr	ra


