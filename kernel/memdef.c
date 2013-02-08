#include "memdef.h"

const size_t page_sizes[] = {
	1024 * 1024,
	64 * 1024,
	4 * 1024,
	1024,
};

//Base-2 logarithms of page_sizes
const size_t page_powers[] = {
	20,
	16,
	12,
	10,
};
