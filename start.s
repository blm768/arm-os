.section .init

.global _start
_start:
bl kmain

.section .text

.global error
error:
	mov r0, #1
	b error
	