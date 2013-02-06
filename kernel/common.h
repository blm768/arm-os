#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stddef.h>

typedef signed char byte;
typedef unsigned char ubyte;

typedef unsigned int  uint;
typedef unsigned long ulong;

extern void error(uint);

void word_copy(void* dest, const void* src, size_t num);

static inline void byte_copy(void* dest, const void* src, size_t num) {
	for(size_t i = 0; i < num; ++i) {
		((ubyte*)dest)[i] = ((ubyte*)src)[i];
	}
}

static inline void* memcpy(void* dest, const void* src, size_t num) {
	word_copy(dest, src, num >> 3);
	byte_copy(dest, src, num & 0x7);
	return dest;
}

//To do: move?
#define IO_BASE 0xF2000000

#endif
