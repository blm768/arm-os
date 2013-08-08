#include "../../memory.h"

#include "platform/current/console.h"

void get_memory_map() {
	MemoryChunk* chunk = &(mem_chunks[0]);
	chunk -> start = KERNEL_PHYS_END;
	chunk -> end = (void*)(MAX_PHYS_PAGES * PAGE_SIZE);
}

void map_io_area() {
	map_pages(SERIAL_BASE, (void*)0x16000000, 1);
}

