#ifndef _MEMORY_H
#define _MEMORY_H

#include "common.h"

#include "platform/current/memdef.h"
#include "platform/current/memory.h"

typedef struct {
	void* start;
	void* end;
	void* free_start;
} MemoryChunk;

extern MemoryChunk mem_chunks[MAX_MEMORY_CHUNKS];

extern void get_memory_map();

void init_phys_allocators();

typedef struct {
	void* next;
} RootPage;

typedef struct AllocChunk {
	struct AllocChunk* next_free;
} AllocChunk;

void* virt_to_phys(void* virt);

static inline void* phys_to_virt(void* phys) {
	return (void*)((size_t)PHYS_BASE + (size_t)phys);
}

void* alloc_phys_page();
void free_phys_page(void* page);

void* alloc_virt(size_t size);
void* free_virt(void* ptr);

void map_pages(void* virt, void* phys, size_t count);
//void subdivide_page(void* phys, size_t level);
//void get_subpage(void* page, size_t n, size_t level);

//To do: error checking.
/*
static inline void* alloc_pages(size_t size) {
	
}
*/

extern void map_io_area();

#endif

