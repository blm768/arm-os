#include "common.h"

#include "console.h"
#include "driver.h"
#include "platform/current/interrupt.h"
#include "memory.h"
#include "thread.h"

#ifndef KMAIN_ARGS
	#define KMAIN_ARGS
#endif

//Currently, kmain uses the interrupt stack.
//It might overwrite ATAGs, etc. if care is not used.
//TODO: allocate a stack elsewhere?
void kmain(KMAIN_ARGS) {
	get_memory_map();
	map_io_area();
	bool status = init_console();
	if(status) {
		init_phys_allocators();
		//Drivers must be loaded before any heap allocations
		//because driver images are stored at the beginning of the heap.
		load_drivers();

		interrupt_init();
		enable_irqs();
		//enable_irq(cpu_timer);
	} else {
		//To do: error handling.
	}
}

