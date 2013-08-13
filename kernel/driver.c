#include "driver.h"

#include "console.h"

void load_drivers() {
	DriverEntry* entries = &first_driver_entry;
	for(size_t i = 0; i < num_drivers; ++i) {
		DriverEntry* entry = entries + i; writeln(entry->name);
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
		//Only PT_LOAD segments of drivers are loaded.
		//TODO: document or change.
		if(segment->type != PT_LOAD) {
			continue;
		}


	}
}

