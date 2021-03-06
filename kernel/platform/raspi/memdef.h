#ifndef _MEMDEF_H
#define _MEMDEF_H

#include "../../common.h"

#include "math.h"

#define PAGE_LEVELS 4

#define PAGE_SIZE_0 (1024 * 1024)

//The size of a section relative to the smallest page size
#define SECTION_RELATIVE_SIZE 1024

#define PAGE_POWER_MIN 10

//Available page sizes on the machine
extern const size_t page_sizes[PAGE_LEVELS];

//Page sizes relative to the smallest page size
extern const size_t rel_page_sizes[PAGE_LEVELS];

//Base-2 logarithm of page_sizes
extern const size_t page_powers[PAGE_LEVELS];

//Note: must be synchronized with start.s
#define NUM_PHYS_PAGES 256

//Slightly convoluted math avoids undefined behavior.
//To do: start using something like SIZE_T_MAX for portability?
#define PHYS_BASE (0xFFFFFFFF - (NUM_PHYS_PAGES * PAGE_SIZE_0) + 1)

#define IO_BASE		(PHYS_BASE - PAGE_SIZE_0)

extern void* kernel_start;
extern void* kernel_end;
//To do: make kernel_page_base or something?
extern void* kernel_base;

//To do: use smaller pages?
#define KERNEL_PAGE_START (void*)ROUND_DOWN((size_t)kernel_start, PAGE_SIZE_0)
//Rounded up to the nearest page
#define KERNEL_PAGE_END (void*)ROUND_UP((size_t)kernel_end, PAGE_SIZE_0)

#define KERNEL_PHYS_START ((void*)(KERNEL_PAGE_START - kernel_base))
#define KERNEL_PHYS_END   ((void*)(KERNEL_PAGE_END   - kernel_base))

#define HEAP_START ((void*)0xC8000000)
#define HEAP_END   ((void*)IO_BASE)

#endif
