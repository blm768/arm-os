.section .text
.align 2

INTERRUPT_BASE = 0x7E00B000
.global interrupt_pending
interrupt_pending = 0x7E00B200

.global irq_enable
#irq_enable = 0x7E00B210
irq_enable:
	.word 0, 0, 0
.align 2

.global irq_disable
irq_disable = 0x7E00B21C


	