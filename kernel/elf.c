#include "elf.h"

const char* elf_magic = "\x7f""ELF";

bool elf_is_valid(ElfHeader* header) {
	//TODO: validate the rest of the header.
	for(size_t i = 0; i < 4; ++i) {
		if(header->magic[i] != elf_magic[i]) {
			return false;
		}
	}
	return true;
}

