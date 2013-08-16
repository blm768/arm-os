#ifndef _ELF_H
#define _ELF_H

#include "common.h"

typedef struct {
	char magic[4];
	uint8_t ident[12];
	uint16_t type;
	uint16_t machine;
	uint32_t version;
	uint32_t entry;
	uint32_t ph_offset;
	uint32_t sh_offset;
	uint32_t flags;
	uint16_t header_size;
	uint16_t ph_entry_size;
	uint16_t num_ph_entries;
	uint16_t sh_entry_size;
	uint16_t num_sh_entries;
	uint16_t strtab_entry_offset;
} ElfHeader;

enum ProgramEntryType {
	PT_NULL,
	PT_LOAD,
	PT_DYNAMIC,
	PT_INTERP,
	PT_NOTE,
	PT_SHLIB,
	PT_PHDR,
};

enum ProgramEntryFlags {
	PF_X = 1,
	PF_R = 2,
	PF_W = 4,
};

typedef struct {
	uint32_t type;
	uint32_t offset;
	uint32_t vaddr;
	uint32_t paddr;
	uint32_t file_length;
	uint32_t memory_size;
	uint32_t flags;
	uint32_t align;
} ElfSegment;

static inline ElfSegment* program_header(ElfHeader* header) {
	return (ElfSegment*)((void*)header + header->ph_offset);
}

extern void load_elf(ElfHeader* header);

extern bool elf_is_valid(ElfHeader* header);

#endif

