#ifndef _MEMORY_H
#define _MEMORY_H

#include "common.h"

#include "arm_memory.h"

//Available page sizes on the machine
extern const size_t page_sizes[PAGE_LEVELS];

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

void* alloc_physical_page(size_t level);

#endif
