#ifndef _ATAGS_H
#define _ATAGS_H

#include "common.h"

//To do: move?
#define MAX_MEMORY_CHUNKS 1

typedef enum {
	none = 0,
	core = 0x54410001,
	mem,
	videotext,
	ramdisk,
	initrd2,
	serial,
	revision,
	videolfb,
	cmdline,
} AtagType;

typedef struct {
	size_t length;
	uint type;
} AtagHeader;

typedef struct {
	uint flags;
	uint page_size;
	uint root_device;
} AtagCore;

extern size_t page_size;

typedef struct {
	void* start;
	void* end;
} AtagMem;

void process_atags(AtagHeader* ptr);
void process_mem_atag(void* ptr);

#endif