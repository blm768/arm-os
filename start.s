.section .init
.align 2

.global _start
_start:
mov sp, #0x8000
bl kmain

.section .text

.global error
error:
	b error
