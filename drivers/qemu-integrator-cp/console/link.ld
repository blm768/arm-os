/*
 * Based on Alex Chadwick's linkscript
 */

ENTRY(_start)

SECTIONS {
	. = kernel_start;
	
	.init : AT(ADDR(.init) - kernel_base) {
		*(.init)
	}

	.text : AT(ADDR(.text) - kernel_base) {
		*(.text)
	}
	
	/* 
	 * To do: move .bss?
	 */
	.data : AT(ADDR(.data) - kernel_base) {
		*(.data .bss .drivers COMMON)
	}
	
	.rodata : AT(ADDR(.rodata) - kernel_base) {
		*(.rodata* COMMON)
	}

	kernel_end = .;
	
	/*.drivers : AT(ADDR(.drivers) - kernel_base) {
		*(.drivers)
	}*/
}

