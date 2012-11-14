.section .init

.global _start
_start:
bl kmain

.global error
error:
	mov r0, #50
	b error
	