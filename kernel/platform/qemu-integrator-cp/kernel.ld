/*
 * Based on Alex Chadwick's linkscript
 */

ENTRY(_start)

/*PHDRS {

}*/

SECTIONS {
	. = kernel_start;
	
	.text : AT(ADDR(.text) - kernel_base) {
		*(.entry .text)
	}
	
	.rodata : AT(ADDR(.rodata) - kernel_base) {
		*(.rodata* COMMON)
	}

	/* 
	 * To do: move .bss to own output section?
	 */
	.data : AT(ADDR(.data) - kernel_base) {
		*(.data .bss)
		kernel_end = .;
		*(.drivers)
	}
}

