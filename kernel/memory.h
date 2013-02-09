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

typedef struct AllocChunk {
	struct AllocChunk* next_free;
} AllocChunk;

void* virt_to_phys(void* virt);

void* alloc_phys_page(size_t level);
void free_phys_page(void* page, size_t level);

void* alloc_virt_pages(size_t size);
void* free_virt_pages(void* pages);

void map_page(void* phys, void* virt, size_t level);
void subdivide_page(void* phys);

//To do: error checking.
/*
static inline void* alloc_pages(size_t size) {
	
}
*/

#endif
