.section .text
.align 4

.global word_copy
word_copy:
	dest .req r0
	src .req r1
	count .req r2
	fast_count .req r3
	stmdb sp!, {r4-r10, r12}
	
	@Copy as much as possible with ldmia/stmia pairs.
	mov fast_count, count, lsr #3
	@count %= 8
	and count, #7
	
	@Skip the fast loop if needed.
	cmp fast_count, #0
	beq .slow_copy
	.fast_loop:
		ldmia src!, {r4-r10, r12}
		stmia dest!, {r4-r10, r12}
		subs fast_count, #1
		bne .fast_loop
	.slow_copy:
		cmp count, #0
		beq .copy_done
	.slow_loop:
		ldmia src!, {r4}
		stmia dest!, {r4}
		subs count, #1
		bne .slow_loop
	
	.copy_done:
	.unreq dest
	.unreq src
	.unreq count
	.unreq fast_count
	
	ldmia sp!, {r4-r10, r12}
	bx lr
