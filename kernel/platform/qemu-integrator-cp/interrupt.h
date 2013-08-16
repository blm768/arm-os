#ifndef _PLATFORM_INTERRUPT_H
#define _PLATFORM_INTERRUPT_H

#include "common.h"

#include "cpu/current/interrupt.h"

typedef enum {
	none
} IRQ;

extern uint32_t irq_enable[3];
extern uint32_t irq_disable[3];

static inline void enable_irq(IRQ irq) {
	const size_t shift = irq & 31;
	const size_t offset = irq >> 5;
	irq_enable[offset] |= (1 << shift);
}

static inline void disable_irq(IRQ irq) {
	const size_t shift = irq & 31;
	const size_t offset = irq >> 5;
	irq_enable[offset] &= ~(1 << shift);
}

#endif

