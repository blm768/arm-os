#include "arm_memory.h"

//16KB-aligned
size_t root_page_table[4096] __attribute__((__aligned__(16384)));

const size_t page_sizes[] = {
	1024 * 1024,
	64 * 1024,
	4 * 1024,
	1024,
};