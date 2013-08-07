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
		chunk->start = (void*)p2_round_up((size_t)chunk->start, PAGE_SIZE);
		chunk->end = (void*)p2_round_down((size_t)chunk->end, PAGE_SIZE);
		chunk->free_start = chunk->start; tmp_mapping_page = alloc_virt(PAGE_SIZE);
	}
}

void* alloc_phys_page() {
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
				*(ubyte**)chunk->free_start += PAGE_SIZE;
				return page;
			}
		}
		//If we reach this, there are no root pages left.
		return NULL;
	}
}

void free_phys_page(void* page) {
	//To do: watermark deallocation?
	RootPage* next_page = first_free_root_page;
	((RootPage*)page)->next = next_page;
	first_free_root_page = (RootPage*)page;
}

void* alloc_virt(size_t size) {
	size = p2_round_up(size, PAGE_SIZE);
	if((size_t)(HEAP_END - heap_watermark) <= size) {
		void* result = heap_watermark;
		heap_watermark += size;
		return result;
	}
	return NULL;
}

