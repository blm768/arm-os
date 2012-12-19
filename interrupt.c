#include "interrupt.h"
#include "timer.h"

void c_irq_handler() {
	cpu_timer_ack();
}

void c_swi_handler() {
	
}
