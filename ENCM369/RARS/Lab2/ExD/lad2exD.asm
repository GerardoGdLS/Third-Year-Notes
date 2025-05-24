# stub1.asm
# ENCM 369 Summer 2024 Lab 2
# This program has complete start-up and clean-up code, and a "stub"
# main function.

# BEGINNING of start-up & clean-up code.  Do NOT edit this code.
	.data
exit_msg_1:
	.asciz	"***About to exit. main returned "
exit_msg_2:
	.asciz	".***\n"
main_rv:
	.word	0
	.data
	.globl alpha
alpha:
	.word 0xb1, 0xe1, 0x91, 0xc1, 0x81, 0xa1, 0xf1, 0xd1
	.globl beta
beta:
	.word 0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70
	
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

# Below is the stub for main. Edit it to give main the desired behaviour.

# int main(void)
#
# local variable	register
#   int *p		s0 
#   int *q		s1
#   int *guard		s2
#   int max		s3  
#   int i		s4
	.text
	.globl	main
main:
	la 	s0, beta # p = beta
	
	la	s1, alpha # q = alpha
	addi	s1, s1, 28 # q = q + 7
	
	la	s2, beta # guard = alpha
	addi	s2, s2, 32 # guard = guard + 8
	
	la	t0, alpha
	lw	s3, 0(t0) # max = alpha[0]
	
	li	s4, 1 # i = 1
	
	li	t0, 8 # t0 = 8
L1:
	beq	s4, t0, L2 # if (i == 8) goto L2
	bgt	s4, t0, L2 # if (i > 8) goto L2
	slli	t1, s4, 2 # t1 = i * 4
	la	t2, alpha # t2 = alpha
	add	t3, t2, t1 # t3 = &alpha[i]
	lw	t4, (t3) #t4 = alpha[i]
	bgt	t4, s3, L3 # if (alpha[i] > max) goto L3
	addi	s4, s4, 1 # i++
	j L1
	
L3:
	mv	s3, t4 # max = alpha[i]
	addi	s4, s4, 1 # i++
	j L1
	
L2:
	beq	s0, s2, L4 # if (p == guard) goto L4
	lw	t0, (s0) # t0 = *p
	sw	t0, 0(s1) # *q = t0
	addi	s0, s0, 4 # p++
	addi	s1, s1, -4 # q--
	j L2
	
L4:
	li      a0, 0   # return value from main = 0
	jr	ra
