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
				if(mem_chunk < MAX_MEMORY_CHUNKS) {
					AtagMem* mem = (AtagMem*)(ptr + 1);
					MemoryChunk* chunk = mem_chunks + mem_chunk;
					chunk->start = mem->start;
					chunk->end = mem->start + mem->size;
					++mem_chunk;
					write("Start: ");
					write_ptr(chunk->start);
					write_newline();
					write("End: ");
					write_ptr(chunk->end);
					write_newline();
				} else {
					die("Unable to process ATAG_MEM; MAX_MEMORY_CHUNKS too low");
				}
				break;
		}
		*(uint**)&ptr += ptr->length;
	}
}
