#include "arm_memory.h"

#include "memory.h"

//16KB-aligned
PageEntry root_page_table[4096] __attribute__((__aligned__(16384)));

//Declared in memory.h
//To do: allow for other levels.
//To do: validation?
void map_page(void* phys, void* virt, size_t level) {
	PageEntry* entry = root_page_table + ((size_t)phys >> page_powers[0]);
	entry->ptr = (void*)((size_t)virt | ENTRY_TYPE_SECTION);
}