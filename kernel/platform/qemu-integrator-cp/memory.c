#include "../../memory.h"

void get_memory_map() {
	MemoryChunk* chunk = &(mem_chunks[0]);
	chunk -> start = KERNEL_PHYS_END;
	chunk -> end = (void*)(MAX_PHYS_PAGES * PAGE_SIZE);
}

