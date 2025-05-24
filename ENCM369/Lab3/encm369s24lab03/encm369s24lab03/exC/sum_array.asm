# sum_array.asm
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
	.globl aaa
aaa:	.word 11, 11, 3, -11
	.data
	.globl bbb
bbb:	.word 200, -300, 400, 500
	.data
	.globl ccc
ccc:	.word -2, -3, 2, 1, 2, 3
	.text
	.globl	main
main:
	addi	sp, sp, -32	#grow stack
	sw	ra, 12(sp)	#store ra
	sw	s2, 8(sp)	#store s2
	sw	s1, 4(sp)	#store s1
	sw	s0, 0(sp)	#store s0
	
	li	s2, 2000	#s2 = 2000
	la	a0, aaa		#a0 = &aaa
	li	a1, 4		#a1 = 4
	li	a2, 9		#a2 = 9
	jal	sum_of_sats	#call sum_of_sats
	mv	s0, a0		#s0 = a0
	la	a0, bbb		#a0 = &bbb
	li	a1, 4		#a1 = 4
	li	a2, 250		#a2 = 250
	jal	sum_of_sats	#call sum_of_sats
	mv	s1, a0		#s1 = a0
	la	a0, ccc		#a0 = &ccc
	li	a1, 6		#a1 = 6
	li	a2, 2		#a2 = 2
	jal	sum_of_sats	#call sum_of_sats
	mv	t0, a0		#t0 = a0
	add	t0, t0, s0	#t0 += s0
	add	t0, t0, s1	#t0 += s1
	add	s2, s2, t0	#s2 += t0
	li      a0, 0   	# return value from main = 0
	
	lw	s0, 0(sp)	#restore s0
	lw	s1, 4(sp)	#restore s1
	lw	s2, 8(sp)	#restore s2
	lw	ra, 12(sp)	#restore ra
	addi	sp, sp, 32	#shrink stack
	jr	ra		#return to caller
	
	.text
	.globl	sum_of_sats
sum_of_sats:
	addi	sp, sp, -32	#grow stack
	sw	ra, 20(sp)	#store ra
	sw	s4, 16(sp)	#store s4
	sw	s3, 12(sp)	#store s3
	sw	s2, 8(sp)	#store s2
	sw	s1, 4(sp)	#store s1
	sw	s0, 0(sp)	#store s0
	
	li	s4, 0		#s4 = 0
	li	s3, 0		#s3, = 0
	mv	s0, a0		#s0 = a0
	mv	s1, a1		#s1 = a1
	mv	s2, a2		#s2 = a2
L1:
	bge	s3, s1, L2	#if (i >= n) goto L2
	slli	t1, s3, 2	#t1 = i * 4
	add	t5, s0, t1	#t5 = &a[i}
	lw	t5, (t5)	#t5 = a[i]
	mv	a0, t5		#a0 = t5
	mv	a1, s2		#a1 = s2
	jal	sat		#call sat
	add	s4, s4, a0	#s4 = s4 + r.v of sat
	addi	s3, s3, 1	#i++
	j	L1		#return to top
L2:
	mv	a0, s4		#a0 = s4
	
	lw	s0, 0(sp)	#restore s0
	lw	s1, 4(sp)	#restore s1
	lw	s2, 8(sp)	#restore s2
	lw	s3, 12(sp)	#restore s3
	lw	s4, 16(sp)	#restore s4
	lw	ra, 20(sp)	#restore ra
	addi	sp, sp, 32	#shrink stack
	jr	ra		#return to caller
	
	.text
	.globl	sat
sat:
	ble	a0, a1, L3	#if (x <= b) goto L3
	mv	a0, a1		#a0 = a1
	j	L5		#goto L5
L3:
	sub	t2, zero, a1	#t2 = -b
	bge	a0, t2, L4	#if (x >= -b) goto L4
	mv	a0, t2		#a0 = t2
	j	L5		#goto L5
L4:
	mv	a0, a0		#a0 = a0
L5:
	jr	ra		#return to caller
