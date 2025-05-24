# write-to-text.asm
# Part of ENCM 369 Summer 2024 Lab 2 Exercise E

# Here RARS works like many real operating system.  Programs are normally
# not allowed to modify their own instructions.

	.text
code:	
	la	t0, code
	sw	zero, (t0)
	addi	a7, zero, 10		# a7 = ecall code for exit
	ecall
