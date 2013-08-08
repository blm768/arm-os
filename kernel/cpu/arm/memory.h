#ifndef _CPU_MEMORY_H
#define _CPU_MEMORY_H

#include "common.h"

#include "platform/current/memory.h"

//To do: verify.
#define SECTION_CACHEABLE 1 << 3
#define SECTION_BUFFERABLE 1 << 2

#define ENTRY_HIGH_BIT (1 << 4)

#define ADDRESS_MASK_SECTION (~((1 << 20) - 1))

#define ENTRY_TYPE_MASK 0x3
#define ENTRY_TYPE_ABSENT 0
#define ENTRY_TYPE_SECTION 0b10
#define ENTRY_TYPE_COARSE 0b01
#define ENTRY_TYPE_FINE 0b11

typedef struct {
	void* ptr;
} PageEntry;

#endif
