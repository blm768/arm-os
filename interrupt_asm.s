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
	
@Partially based on the dwelch67 bootloader code


