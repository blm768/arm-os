#include "driver.h"

#include "console.h"

void load_drivers() {
	DriverEntry* entries = &first_driver_entry;
	for(size_t i = 0; i < num_drivers; ++i) {
		DriverEntry* entry = entries + i;
		writeln(entry->name);
		load_driver((ElfHeader*)(entry->image));
	}
}

void load_driver(ElfHeader* header) {
	ElfSegment* segments = program_header(header);
}

