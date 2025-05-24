# ENCM 369 Summer 2024 Lab 4
# Code fragment for use in Exercise B.

	.data
foo:	.word	0, 0, 0, 0
alpha:	.word	0x123
beta:	.word	0x456

	.text
	lw	t1, alpha
	li	t2, 0x789
	sw	t2, beta, t3
