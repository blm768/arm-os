@Physically placed at 0x8000
.section .init
.align 2

@The bootloader puts root_page_table at this physical address.
.equ .p_root_page_table, (root_page_table - 0xC000000)

@Note: must be synchronized with memdef.h
.equ num_phys_pages, 256

.global _start
_start:
	@Set up stack.
	mov sp, #0x8000
	
	@Store bootloader parameters.
	stmdb sp!, {r0-r2}
	
	@Set up paging:
	
	@Inform the MMU of the root page table's location.
	@TTBR1 is used for the kernel page table.
	ldr r0, =.p_root_page_table
	mcr p15, 0, r0, c2, c0, 0
	mcr p15, 0, r0, c2, c0, 1
	@Set TTBCR so addresses above 0x80000000 are mapped using TTBR1:
	mrc p15, 0, r0, c2, c0, 2
	bic r0, #7
	orr r0, #1
	@mcr p15, 0, r0, c2, c0, 2

	@Identity map the first 1MB.
	mov r1, #0x2
	str r1, [r0]
	
	@Map the higher "half".
	@TODO: make sure the number of pages is high enough to cover the kernel.
	mov r0, #8
	mov r1, #0x12
	@This corresponds to the virtual address 0xC0000000.
	ldr r2, =(.p_root_page_table + ((4096 - 1024) * 4))
	.map_upper:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_upper
	
	@Map the physical memory area.
	mov r0, #num_phys_pages
	mov r1, #0x12
	ldr r2, =(.p_root_page_table + (4096 - num_phys_pages) * 4)
	.map_phys:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_phys
	

	@Map the I/O area. (0x20000000 phys)
	ldr r1, =(io_base + 0x12)
	ldr r2, =(.p_root_page_table + ((4096 - num_phys_pages - 1) * 4))
	str r1, [r2]
	
	@Set domain 0 to have no access restrictions.
	mov r0, #0x3
	mcr p15, 0, r0, c3, c0, 0

	@Enable the MMU.
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x1
	mcr p15, 0, r0, c1, c0, 0

	@Enter kmain.
	bl kmain@=(kmain - 0xC0000000)
	
	.loop:
	b .loop

.section .text
.align 2

@TODO: remove?
.section .data
@16KB aligned
.align 12

