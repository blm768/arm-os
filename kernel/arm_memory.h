#ifndef _ARM_MEMORY_H
#define _ARM_MEMORY_H

#include "common.h"

#define PAGE_LEVELS 4

//To do: verify.
#define SECTION_CACHEABLE 1 << 3
#define SECTION_BUFFERABLE 1 << 2

#define ENTRY_TYPE_SECTION 0b10;

typedef struct {
	void* ptr;
} PageEntry;

#endif
