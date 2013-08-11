#ifndef _ELF_H
#define _ELF_H

#include "common.h"

typedef struct {
	ubyte ident[16];
	ushort type;
	ushort machine;
	uint version;
	uint entry;
	uint ph_offset;
	uint sh_offset;
	uint flags;
	ushort header_size;
	ushort ph_entry_size;
	ushort num_ph_entries;
	ushort sh_entry_size;
	ushort num_sh_entries;
	ushort strtab_entry_offset;
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

typedef struct {
	uint type;
	uint offset;
	uint vaddr;
	uint paddr;
	uint file_length;
	uint memory_size;
	uint flags;
	uint align;
} ElfProgramHeader;

extern void load_elf(ElfHeader* header);

#endif

