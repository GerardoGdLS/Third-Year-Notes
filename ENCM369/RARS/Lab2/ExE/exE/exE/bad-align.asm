# bad-align.asm
# Part of ENCM 369 Summer 2024 Lab 2 Exercise E

	.data
	# int words[] = {0x01234567, 0x89abcdef};
words:	.word	0x01234567, 0x89abcdef

	.text
	la	t0, words	# t0 = &words[0]
	lw	t1, 0(t0)	# this load will be fine
	lw	t2, 4(t0)	# this load will also work
	lw	t3, 2(t0)	# try lw with address not a multiple of 4
	addi	a7, zero, 10	# a7 = ecall code for exit
	ecall
