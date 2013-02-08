#ifndef _MEMORY_H
#define _MEMORY_H

#include "common.h"

#include "arm_memory.h"
#include "memdef.h"

//To do: move?
#define MAX_MEMORY_CHUNKS 1

typedef struct {
	void* start;
	void* end;
	void* free_start;
} MemoryChunk;

extern MemoryChunk mem_chunks[MAX_MEMORY_CHUNKS];

void init_page_allocators();

typedef struct {
	void* next;
} RootPage;

typedef struct VirtualPage {
	struct VirtualPage* next_free;
} VirtualPage;

void* alloc_physical_page(size_t level);
void free_physical_page(void* page, size_t level);

void* alloc_virtual_pages(size_t size);
void* free_virtual_pages(void* pages);

void map_page(void* phys, void* virt, size_t level);

//To do: error checking.
/*
static inline void* alloc_pages(size_t size) {
	
}
*/

#endif
