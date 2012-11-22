#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "bitutils.h"
#include "common.h"

typedef enum {
	aux = 29,
	i2c_spi_slv = 43,
	pwa0 = 45,
	pwa1 = 46,
	smi = 48,
	gpio0 = 49,
	gpio1,
	gpio2,
	gpio3,
	i2c = 53,
	spi = 54,
	pcm = 55,
	uart = 57,
	arm_timer = 64,
	mailbox0,
	doorbell0,
	doorbell2,
	gpu_halt0,
	gpu_halt1,
	access_error_a,
	access_error_b,
} IRQ;

extern uint irq_enable[3];
extern uint irq_disable[3];

static inline void irq_init() {
	
}

static inline void enable_irq(IRQ irq) {
	clear_word_and_set_bit(irq_enable, irq);
}

static inline void disable_irq(IRQ irq) {
	clear_word_and_set_bit(irq_disable, irq);
}

#endif
