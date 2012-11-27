@Partially based on the dwelch67 bootloader code

.equ user_mode,  0x10
.equ fiq_mode,   0x11
.equ irq_mode,   0x12
.equ svc_mode,   0x13
.equ abort_mode, 0x17
.equ undef_mode, 0x1b
.equ int_off,    0xc0

.section .text
.align 2

.global halt
halt:
	b halt

.global enable_irqs
enable_irqs:
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr, r0
	mov pc, lr

.global disable_irqs
disable_irqs:
	mrs r0, cpsr
	orr r0, r0, #0x80
	msr cpsr, r0
	mov pc, lr
	
.global irq_handler
irq_handler:
	@Note: lr and spsr must be saved before making calls to other functions.
	@What else needs to be saved?
	sub lr, lr, #4
	
	@Save SPSR.
	mrs r0, spsr
	
	@Switch to system mode.
	mrs r1, cpsr
    bic r1, r1, #0xDF
    orr r1, r1, #0x1F
    msr cpsr, r1
	
	stmdb sp!, {r0, lr}
	bl c_irq_handler
	ldmia sp!, {r0, lr}
	
	@Return to IRQ mode.
	mrs r1, cpsr
    bic r1, r1, #0xDF
    orr r1, r1, #0x92
    msr cpsr, r1
	
	@Restore spsr.
	msr spsr, r0
	movs pc, lr
	
.global asm_interrupt_init
asm_interrupt_init:
	@Set up IVT.
	ldr r0, =.ivt
	mov r1, #0x0000
	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}
	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}
	mov pc, lr

.global asm_irq_init
asm_irq_init:
	@Set up IRQ stack
	mrs r0, cpsr
	mov r1, #irq_mode | int_off
	msr cpsr, r1
	mov sp, #0x8000
	msr cpsr, r0
	mov pc, lr

.section .data
.align 2

INTERRUPT_BASE = 0x7E00B000

.global interrupt_pending
interrupt_pending_special = 0x7E00B200
interrupt_pending_normal =  0x7E00B204

.global irq_enable
irq_enable = 0x7E00B210

.global irq_disable
irq_disable = 0x7E00B21C

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
	.word halt
	.word halt
	.word halt
	.word halt
	.word halt
	.word irq_handler
	.word halt
