#include "arm_memory.h"

#include "memory.h"

//16KB-aligned
PageEntry root_page_table[4096] __attribute__((__aligned__(16384)));

//To do: how to handle the lowest page?
//To do: error checking (i.e. unmapped pages)
void* virt_to_phys(void* virt) {
	PageEntry entry = root_page_table[(size_t)virt >> page_powers[0]];
	size_t type = (size_t)entry.ptr & ENTRY_TYPE_MASK;
	if(type == ENTRY_TYPE_SECTION) {
		return (void*)((size_t)entry.ptr & ADDRESS_MASK_SECTION);
	}
	return NULL;
}

//Declared in memory.h
//To do: allow for other levels.
//To do: validation?
void map_pages(void* phys, void* virt, size_t count) {
	PageEntry* entry = root_page_table + ((size_t)phys >> page_powers[0]);
	while(count > 0) {
	//if((count % !(phys & ~ADDRESS_MASK_SECTION)) {
		entry->ptr = (void*)((size_t)virt | ENTRY_HIGH_BIT | ENTRY_TYPE_SECTION);
		virt += page_sizes[0];
		entry += 1;
		--count;
	//}
	}
}