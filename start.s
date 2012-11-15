.section .init

.global _start
_start:
bl kmain

.section .text

.global error
error:
	b error
	