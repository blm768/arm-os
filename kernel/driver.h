#ifndef _DRIVER_H
#define _DRIVER_H

#include "common.h"

#include "elf.h"

typedef struct {
	char* name;
	void* image;
} DriverEntry;

extern size_t num_drivers;
extern DriverEntry first_driver_entry;

extern void load_drivers();
extern void load_driver(ElfHeader* header);

#endif

