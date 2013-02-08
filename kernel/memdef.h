#ifndef _MEMDEF_H
#define _MEMDEF_H

#include "common.h"

#define PAGE_LEVELS 4

//Available page sizes on the machine
extern const size_t page_sizes[PAGE_LEVELS];

//Base-2 logarithm of page_sizes
extern const size_t page_powers[PAGE_LEVELS];

#define IO_BASE		0xF2000000
#define IO_BASE_CC	0xF9000000

extern void* kernel_start;
extern void* kernel_end;
//To do: make kernel_page_base or something?
extern void* kernel_base;

//To do: use smaller pages?
//Rounded down to the nearest page
#define KERNEL_PAGE_START (kernel_start - (kernel_start % page_sizes[0]))
//Rounded up to the nearest page
#define KERNEL_PAGE_END   (kernel_end - (kernel_end % page_sizes[0]) + ((kernel_end % page_sizes[0]) ? page_powers[0] : 0))

#define KERNEL_PHYS_START ((void*)(KERNEL_PAGE_START - kernel_base))
#define KERNEL_PHYS_END   ((void*)(KERNEL_PAGE_END   - kernel_base))

#endif
