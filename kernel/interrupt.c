#include "interrupt.h"
#include "platform/current/timer.h"

void c_irq_handler() {
	cpu_timer_ack();
}

void c_swi_handler() {
	
}
