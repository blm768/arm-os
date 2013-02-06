#include "arm_memory.h"

size_t root_page_table[4096];

const size_t page_sizes[] = {
	1024 * 1024,
	64 * 1024,
	4 * 1024,
	1024,
};