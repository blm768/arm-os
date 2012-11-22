
@Only present in QEMU binaries
.section .ivt
.align(2)
b _start
	
.section .init
.align 2

.global _start
_start:
mov sp, #0x8000
/*
ldr r0,=0x20200000
mov r1,#1
lsl r1,#18
str r1,[r0,#4]
mov r1,#1
lsl r1,#16
str r1,[r0,#40]
*/
bl kmain
.loop:
b .loop

.section .text
.align 2

.global error
error:
	b error
