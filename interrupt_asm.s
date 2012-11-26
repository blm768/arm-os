@Partially based on the dwelch67 bootloader code

.section .text
.align 2

INTERRUPT_BASE = 0x7E00B000

.global interrupt_pending
interrupt_pending_special = 0x7E00B200
interrupt_pending_normal =  0x7E00B204

.global irq_enable
irq_enable = 0x7E00B210

.global irq_disable
irq_disable = 0x7E00B21C

.global irq_handler
irq_handler:
	@Note: lr and spsr must be saved before making calls to other functions.
	@What else needs to be saved?
	@What is the offset on lr?
	mov pc, lr
	
.global asm_irq_init
asm_irq_init:
	ldr r0, =.ivt
	mov r1, #0x0000
	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}
	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}
	mov pc, lr

.section .data
.align 2

.ivt:
	ldr pc, .isrs
	ldr pc, .isrs + 4
	ldr pc, .isrs + 8
	ldr pc, .isrs + 12
	ldr pc, .isrs + 16
	ldr pc, .isrs + 20
	ldr pc, .isrs + 24
	ldr pc, .isrs + 28
.isrs:
	.word _start
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
