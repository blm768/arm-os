#include "atags.h"

#include "memory.h"
#include "textcons.h"

void process_atags(AtagHeader* ptr) {
	if(ptr->type != core) {
		die("Invalid type for first ATAG (or ATAGs not present)");
	}
	if(ptr->length <= 2) {
		die("Invalid length for ATAG_CORE");
	}
	write_uint(ptr->length);
	write_newline();
	*(uint**)&ptr += ptr->length;
	
	size_t mem_chunk = 0;
	while(ptr->type != none) {
		write("Length: ");
		write_uint(ptr->length);
		write_newline();
		switch(ptr->type) {
			case mem:
				//Note: this _might_ not be accurate on all systems.
				if(mem_chunk < MAX_MEMORY_CHUNKS) {
					AtagMem* mem = (AtagMem*)(ptr + 1);
					MemoryChunk* chunk;
					chunk->start = mem->start;
					chunk->end = mem->start + mem->size;
					//Clip the chunk against the kernel.
					if(chunk->start >= KERNEL_PAGE_START && chunk->start < KERNEL_PAGE_END) {
						chunk->start = KERNEL_PAGE_END;
					}
					if(chunk->end > KERNEL_PAGE_START && chunk->end <= KERNEL_PAGE_END) {
						chunk->end = KERNEL_PAGE_START;
					}
					//If we still have a chunk, save it.
					if(chunk->start < chunk->end) {
						mem_chunks[mem_chunk] = chunk;
						++mem_chunk;
					}
				} else {
					die("Unable to process ATAG_MEM; MAX_MEMORY_CHUNKS too low");
				}
				break;
		}
		*(uint**)&ptr += ptr->length;
	}
}
