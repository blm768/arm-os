#include "common.h"

#include "atags.h"
#include "gpio.h"
#include "textcons.h"
#include "interrupt.h"
#include "memory.h"
#include "string.h"
#include "timer.h"

//To do: peripheral read/write barriers!

void kmain(uint r0, uint system_type, AtagHeader* atags) {
	gpio_set_output(16);
	gpio_set(16);
	//interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	bool status = init_console();
	console.cx = 1;
	if(status) {
		process_atags(atags);
		init_page_allocators();
	} else {
		while(true) {
			gpio_clear(16);
			busy_wait(250000);
			gpio_set(16);
			busy_wait(750000);
		}
	}
}
