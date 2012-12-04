#include "interrupt.h"
#include "timer.h"

void c_irq_handler() {
	acknowledge_cpu_timer();
}

void c_swi_handler() {
	
}
