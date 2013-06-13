/*
 * Based on Alex Chadwick's linkscript
 */

SECTIONS {
	kernel_start = 0xC0000000;
	kernel_base  = 0xC0000000;
	. = 0xC008000;
	
	.init : AT(ADDR(.init) - 0xC000000) {
		*(.init)
	}

	.text : AT(ADDR(.text) - 0xC000000) {
		*(.text)
	}
	
	/* 
	 * To do: move .bss?
	 */
	.data : AT(ADDR(.data) - 0xC000000) {
		*(.data .bss COMMON)
	}
	
	.rodata : AT(ADDR(.rodata) - 0xC000000) {
		*(.rodata* COMMON)
	}
	
	kernel_end = .;

	/DISCARD/ : {
		*(*)
	}
}
