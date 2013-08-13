#include "common.h"

#include "console.h"
#include "driver.h"
#include "platform/current/interrupt.h"
#include "memory.h"
#include "thread.h"

#ifndef KMAIN_ARGS
	#define KMAIN_ARGS
#endif

void kmain(KMAIN_ARGS) {
	get_memory_map();
	map_io_area();
	bool status = init_console();
	if(status) {
		write("Project Greenhorn pre-alpha\n");
		write("---------------------------\n\n");
		write("Drivers: ");
		load_drivers();
		init_page_allocators();
		interrupt_init();
		enable_irqs();
		//enable_irq(cpu_timer);
	} else {
		//To do: error handling.
	}
}

