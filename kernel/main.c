#include "common.h"

//#include "textcons.h"
//#include "interrupt.h"
#include "memory.h"
#include "string.h"

#ifndef KMAIN_ARGS
	#define KMAIN_ARGS
#endif

void kmain(KMAIN_ARGS) {
	//interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	//bool status = init_console();
	bool status = true;
	if(status) {
		//process_atags(atags);
		init_page_allocators();
	} else {
		//To do: error handling.
	}
}
