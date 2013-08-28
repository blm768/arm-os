.section .text
.align 2

.global _start
_start:
	bl main
	.loop:
		b .loop

