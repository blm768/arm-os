#include "driver.h"

#include "memory.h"

#include "console.h"

void alloc_driver_stack() {

}

static void* driver_segment_start = DRIVER_START;

//Allocates virtual memory for a driver ELF segment
void* alloc_driver_segment(size_t size) {
	size_t pages = p2_round_up(size, PAGE_SIZE);
	size_t paged_size = pages * PAGE_SIZE;

	void* allocated = driver_segment_start;
	void* new_start = allocated + paged_size;
	if(new_start >= DRIVER_END) {
		return NULL;
	}
	driver_segment_start = new_start;

	return allocated;
}

void load_drivers() {
	DriverEntry* entries = &first_driver_entry;
	for(size_t i = 0; i < num_drivers; ++i) {
		DriverEntry* entry = entries + i;
		writeln(entry->name);
		load_driver((ElfHeader*)(entry->image));
	}
}

void load_driver(ElfHeader* header) {
	bool valid = elf_is_valid(header);
	if(!valid) {
		die("Invalid driver.");
	}
	size_t num_segments = header->num_ph_entries;
	size_t segment_len = header->ph_entry_size;
	ElfSegment* segments = program_header(header);
	for(size_t i = 0; i < num_segments; ++i) {
		ElfSegment* segment = segments + i;

		//TODO: loading for other segment types?
		if(segment->type != PT_LOAD) {
			continue;
		}

		void* virt = alloc_driver_segment(0);
		if(!virt) {
			die("Unable to allocate address space for driver segment");
		}

		void* phys = virt_to_phys(segment);
		write_ptr(phys);
		write_char('\n');
	}
}

