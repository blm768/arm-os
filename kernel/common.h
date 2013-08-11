#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stddef.h>

typedef signed char byte;
typedef unsigned char ubyte;

typedef unsigned short ushort;
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
	void* dest_saved = dest;
	//The number of bytes copied from dest/src before we reach word alignment
	size_t dest_head = sizeof(size_t) - ((size_t)dest % sizeof(size_t));
	size_t src_head  = sizeof(size_t) - ((size_t)src % sizeof(size_t));
	if(src_head == dest_head) {
		//Source and destination are similarly aligned; we may be able to use word copies.
		byte_copy(dest, src, dest_head);
		*(char**)dest += dest_head;
		*(char**)src  += dest_head;
		num -= dest_head;
		size_t words = num >> 3;
		//Word-copy as much as possible and byte-copy the rest.
		word_copy(dest, src, words);
		byte_copy(dest + words * sizeof(size_t), src + words * sizeof(size_t), num & 0x7);
	} else {
		//The areas have different alignments; fall back to a byte copy.
		byte_copy(dest, src, num);
	}
	return dest_saved;
}

#endif

