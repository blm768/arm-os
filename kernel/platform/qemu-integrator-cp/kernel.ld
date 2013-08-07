/*
 * Based on Alex Chadwick's linkscript
 */

ENTRY(_start)

SECTIONS {
	. = kernel_start;
	
	.init : AT(ADDR(.init)) {
		*(.init)
	}

	.text : AT(ADDR(.text) - kernel_base) {
		*(.text)
	}
	
	/* 
	 * To do: move .bss?
	 */
	.data : AT(ADDR(.data) - kernel_base) {
		*(.data .bss COMMON)
	}
	
	.rodata : AT(ADDR(.rodata) - kernel_base) {
		*(.rodata* COMMON)
	}
	
	kernel_end = .;
}

