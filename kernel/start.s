
@Only present in QEMU binaries
.section .ivt
.align(2)
b _start
	
@Placed at 0x8000
.section .init
.align 2

.global _start
_start:
	@Set up stack.
	@To do: MOVE THIS! It's right on top of the interrupt stack.
	mov sp, #0x8000
	@Enter kmain.
	bl kmain
	.loop:
	b .loop

.section .text
.align 2

.global error
error:
	b error
