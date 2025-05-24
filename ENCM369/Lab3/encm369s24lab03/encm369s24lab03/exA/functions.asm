# functions.asm
# ENCM 369 Summer 2024
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
	.data
	.globl	cherry
cherry:	.word	0x30000
	.text
	.globl	main
main:
	#prologue
	addi	sp, sp, -32	#grow stack
	sw	ra, 8(sp)	#save ra to stack
	sw	s1, 4(sp)	#save s1 to stack
	sw	s0, 0(sp)	#save s0 to stack
	
	#body
	li	s0, 0x700	#s0 = 0x700
	li	s1, 0x600	#s1 = 0x600
	li	a0, 3		#a0 = 3
	li	a1, 5		#a1 = 5
	li	a2, 6		#a2 = 6
	li	a3, 4		#a3 = 4
	jal	funcA		#call funcA
	add	s1, s1, a0	#banana = banana + r.v of funcA
	la	t0, cherry	#t0 = &cherry
	lw	s2, (t0)	#s2 = *t0
	sub	t1, s1, s0	#t1 = banana - apple
	add	s2, s2, t1	#s2 = cherry + t1
	sw	s2, (t0)	#cherry = s2
	
	#epilogue
	lw	s0, 0(sp)	#restore s0
	lw	s1, 4(sp)	#restore s1
	lw	ra, 8(sp)	#restore ra
	addi	sp, sp, 32	#shrink stack
	li      a0, 0   	# return value from main = 0
	jr	ra		#return to caller
	
	.text
	.globl funcA
funcA:
	#prologue
	addi	sp, sp, -32	#grow stack
	sw	ra, 8(sp)	#store ra
	sw	s1, 4(sp)	#store s1
	sw	s0, 0(sp)	#store s0
	add	s0, a0, zero	#s0 = 3
	add	s1, a1, zero	#s1 = 5
	add	s2, a2, zero	#s2 = 6
	add	s3, a3, zero	#s3 = 4
	
	#body
	mv	a0, s1		#a0 = second
	mv	a1, s0		#a1 = first
	jal	funcB		#call funcB
	mv	s6, a0		#s6 = r.v of funcB
	mv	a0, s3		#a0 = fourth
	mv	a1, s2		#a1 = third
	jal	funcB		#call funcB
	mv	s4, a0		#s4 = r.v of funcB
	mv	a0, s2		#a0 = third
	mv	a1, s3		#a1 = fourth
	jal	funcB		#call funcB
	mv	s5, a0		#s5 = r.v of funcB
	add	t2, s4, s5	#t2 = kiwi + mango
	add	a0, t2, s6	#a0 = t2 + orange
	
	#epilogue
	lw	s0, 0(sp)	#restore s0
	lw	s1, 4(sp)	#restore s1
	lw	ra, 8(sp)	#restore ra
	addi	sp, sp, 32	#shrink stack
	jr	ra		#return to caller
	
	.text
	.globl funcB
funcB:
	slli	t3, a1, 7	#t3 = z * 128
	add	a0, a0, t3	#a0 = y + t3
	jr	ra		#return to caller
