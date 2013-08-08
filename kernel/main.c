#include "common.h"

#include "console.h"
#include "cpu/current/interrupt.h"
#include "memory.h"
#include "thread.h"

#ifndef KMAIN_ARGS
	#define KMAIN_ARGS
#endif

void kmain(KMAIN_ARGS) {
	interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	bool status = init_console();
	if(status) {
		write("Project Greenhorn pre-alpha\n");
		write("---------------------------\n\n");
		get_memory_map();
		write("Available physical memory regions:\n");
		for(size_t i = 0; i < MAX_MEMORY_CHUNKS; ++i) {
			MemoryChunk* chunk = mem_chunks + i;
			write_ptr(chunk->start);
			write(" -> ");
			write_ptr(chunk->end);
			write("\n\n");
		}
		init_page_allocators();
		write("Page allocators initialized.\n");
	} else {
		//To do: error handling.
	}
}
