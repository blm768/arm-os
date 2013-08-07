#include "memory.h"

//16KB-aligned
PageEntry root_page_table[4096] __attribute__((__aligned__(16384)));

//To do: how to handle the lowest page?
//To do: error checking (i.e. unmapped pages)
void* virt_to_phys(void* virt) {
	PageEntry entry = root_page_table[(size_t)virt >> PAGE_SIZE_POWER];
	size_t type = (size_t)entry.ptr & ENTRY_TYPE_MASK;
	if(type == ENTRY_TYPE_SECTION) {
		return (void*)((size_t)entry.ptr & ADDRESS_MASK_SECTION);
	}
	return NULL;
}

//To do: allow for other page levels?
//To do: validation?
void map_pages(void* phys, void* virt, size_t count) {
	PageEntry* entry = root_page_table + ((size_t)phys >> PAGE_SIZE_POWER);
	while(count > 0) {
		entry->ptr = (void*)((size_t)virt | ENTRY_HIGH_BIT | ENTRY_TYPE_SECTION);
		virt += PAGE_SIZE;
		entry += 1;
		--count;
	}
}

