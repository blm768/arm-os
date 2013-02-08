#include "memory.h"

#include "math.h"

MemoryChunk mem_chunks[MAX_MEMORY_CHUNKS] = {{0, 0, 0}};
RootPage* first_free_root_page = NULL;

void init_page_allocators() {
	//For now, memory chunks are rounded to the nearest root-level page.
	for(size_t i = 0; i < MAX_MEMORY_CHUNKS; ++i) {
		MemoryChunk* chunk = mem_chunks + i;
		chunk->start = (void*)round_up((size_t)chunk->start, page_sizes[0]);
		chunk->end = (void*)round_down((size_t)chunk->end, page_sizes[0]);
		chunk->free_start = chunk->start;
	}
}

void* alloc_physical_page(size_t level) {
	if(level == 0) {
		if(first_free_root_page) {
			RootPage* page = first_free_root_page;
			first_free_root_page = page->next;
			return (void*)page;
		} else {
			for(size_t i = 0; i < MAX_MEMORY_CHUNKS; ++i) {
				MemoryChunk* chunk = mem_chunks + i;
				//Is there a free page in this chunk?
				if(chunk->free_start < chunk-> end) {
					void* page = chunk->free_start;
					*(ubyte**)chunk->free_start += page_sizes[0];
					return page;
				}
			}
			//If we reach this, there are no root pages left.
			return 0;
		}
	} else {
		//To do: implement.
		return 0;
	}
}

void free_physical_page(void* page, size_t level) {
	if(level == 0) {
		//To do: watermark deallocation?
		RootPage* next_page = first_free_root_page;
		((RootPage*)page)->next = next_page;
		first_free_root_page = (RootPage*)page;
	}
}
