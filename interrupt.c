#include "interrupt.h"
#include "timer.h"

void c_irq_handler() {
	gpio_clear(16);
}

void c_swi_handler() {
	
}
