#include "memory.h"

#include "math.h"

MemoryChunk mem_chunks[MAX_MEMORY_CHUNKS] = {{0, 0, 0}};
RootPage* first_free_root_page = NULL;

void* heap_watermark = HEAP_START;

//For use only by allocators
static void* tmp_mapping_page;

void init_page_allocators() {
	//For now, memory chunks are rounded to the nearest root-level page.
	for(size_t i = 0; i < MAX_MEMORY_CHUNKS; ++i) {
		MemoryChunk* chunk = mem_chunks + i;
		//This assumes that page sizes are a power of 2.
		chunk->start = (void*)p2_round_up((size_t)chunk->start, page_sizes[0]);
		chunk->end = (void*)p2_round_down((size_t)chunk->end, page_sizes[0]);
		chunk->free_start = chunk->start;
		tmp_mapping_page = alloc_virt(page_sizes[0]);
	}
}

void* alloc_phys_page(size_t level) {
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
			return NULL;
		}
	} else {
		//To do: implement.
		return NULL;
	}
}

void free_phys_page(void* page, size_t level) {
	if(level == 0) {
		//To do: watermark deallocation?
		RootPage* next_page = first_free_root_page;
		((RootPage*)page)->next = next_page;
		first_free_root_page = (RootPage*)page;
	}
}

void* alloc_virt(size_t size) {
	size = p2_round_up(size, page_sizes[PAGE_LEVELS - 1]);
	if((size_t)(HEAP_END - heap_watermark) <= size) {
		void* result = heap_watermark;
		heap_watermark += size;
		return result;
	}
	return NULL;
}

