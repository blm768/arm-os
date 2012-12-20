#include "atags.h"

size_t page_size;

void process_core_atag(AtagCore* core) {
	page_size = core->page_size;
	if(page_size == 4096) {
		gpio_clear(16);
	}
}

void process_atags(AtagHeader* ptr) {
	if(ptr->type != core) {
		//To do: produce error.
		return;
	}
	if(ptr->length <= 2) {
		return;
	}
	process_core_atag((AtagCore*)(ptr + 1));
	*(char**)&ptr += ptr->length;
	while(ptr->type != none) {
		switch(ptr->type) {
			case mem:
				gpio_clear(16);
				break;
		}
		*(char**)&ptr += ptr->length;
	}
}
