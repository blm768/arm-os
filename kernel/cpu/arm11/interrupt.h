#ifndef _CPU_INTERRUPT_H
#define _CPU_INTERRUPT_H

#include "common.h"

#include "platform/current/interrupt.h"

typedef void(*ISR)();

extern void swi();

typedef struct {
	ISR reset;
	ISR undefined;
	ISR swi;
	ISR prefetch;
	ISR data;
	ISR unused;
	ISR irq;
	ISR fiq;
} InterruptHandlers;

extern void _start();

#define isrs (*(InterruptHandlers*)0x20)

extern void enable_irqs();
extern void disable_irqs();

extern void c_irq_handler();

extern void asm_irq_init();
static inline void irq_init() {
	asm_irq_init();
}

extern void asm_interrupt_init();
static inline void interrupt_init() {
	asm_interrupt_init();
	irq_init();
}

#endif

