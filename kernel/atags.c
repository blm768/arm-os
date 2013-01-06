#include "atags.h"

#include "textcons.h"

size_t page_size;

void process_core_atag(AtagCore* core) {
	page_size = core->page_size;
	write_uint(page_size);
	write_newline();
}

void process_atags(AtagHeader* ptr) {
	if(ptr->type != core) {
		die("Invalid type for first ATAG (or ATAGs not present)");
	}
	if(ptr->length <= 2) {
		die("Invalid length for ATAG_CORE");
	}
	process_core_atag((AtagCore*)(ptr + 1));
	*(char**)&ptr += ptr->length;
	while(ptr->type != none) {
		write("Type: ");
		write_uint(ptr->type);
		write_newline();
		switch(ptr->type) {
			case mem:
				break;
		}
		*(char**)&ptr += ptr->length;
	}
}
