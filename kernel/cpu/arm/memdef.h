#ifndef _CPU_MEMDEF_H
#define _CPU_MEMDEF_H

#include "common.h"

#include "platform/current/memdef.h"

#include "math.h"

//#define PAGE_LEVELS 4

#define PAGE_SIZE (1024 * 1024)
//The power of two needed to reach PAGE_SIZE
#define PAGE_SIZE_POWER 20

//The size of a section relative to the smallest page size
//#define SECTION_RELATIVE_SIZE 1024

//#define PAGE_POWER_MIN 10

//Available page sizes on the machine
//extern const size_t page_sizes[PAGE_LEVELS];

//Page sizes relative to the smallest page size
//extern const size_t rel_page_sizes[PAGE_LEVELS];

//Base-2 logarithm of page_sizes
//extern const size_t page_powers[PAGE_LEVELS];

//Note: must be synchronized with memdef.s.inc
#define MAX_PHYS_PAGES 256

//Slightly convoluted math avoids undefined behavior.
//To do: start using something like SIZE_T_MAX for portability?
#define PHYS_BASE ((void*)(0xFFFFFFFF - (MAX_PHYS_PAGES * PAGE_SIZE) + 1))
#define IO_BASE ((void*)(PHYS_BASE - NUM_IO_PAGES * PAGE_SIZE))

//TODO: convert to macros to help constant folding?
extern ubyte kernel_start;
extern ubyte kernel_end;
//TODO: rename to kernel_page_base or something?
extern ubyte kernel_base;

//To do: use smaller pages?
#define KERNEL_PAGE_START ((void*)ROUND_DOWN((size_t)&kernel_start, PAGE_SIZE))
//Rounded up to the nearest page
#define KERNEL_PAGE_END ((void*)ROUND_UP((size_t)&kernel_end, PAGE_SIZE))

#define KERNEL_PHYS_START (KERNEL_PAGE_START - (size_t)&kernel_base)
#define KERNEL_PHYS_END   (KERNEL_PAGE_END   - (size_t)&kernel_base)

#define HEAP_START ((void*)0xC8000000)
#define HEAP_END   ((void*)(PHYS_BASE - NUM_IO_PAGES * PAGE_SIZE))

#endif
