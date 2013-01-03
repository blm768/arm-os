#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stddef.h>

typedef signed char byte;
typedef unsigned char ubyte;

typedef unsigned int  uint;
typedef unsigned long ulong;

extern void error(uint);

static inline void byte_copy(void* dest, void* src, size_t num) {
	for(size_t i = 0; i < num; ++i) {
		((ubyte*)dest)[i] = ((ubyte*)src)[i];
	}
}

#endif