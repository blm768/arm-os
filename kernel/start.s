.include "cpu/current/memdef.s.inc"

.global kernel_start
.global kernel_base

.global max_phys_pages

@Physically placed at 0x8000
.section .init
.align 2

@The bootloader puts root_page_table at this physical address.
.equ .p_root_page_table, (root_page_table - kernel_base)

.global _start
_start:
	@Set up stack.
	mov sp, #0x8000
	
	@Store bootloader parameters.
	stmdb sp!, {r0-r2}

	@Set up paging:
	
	@Inform the MMU of the root page table's location.
	@TTBR1 is used for the kernel page table.
	@To do: actually implement the above.
	ldr r0, =.p_root_page_table
	mcr p15, 0, r0, c2, c0, 0
	mcr p15, 0, r0, c2, c0, 1
	@Set TTBCR so addresses above 0x80000000 are mapped using TTBR1:
	mrc p15, 0, r1, c2, c0, 2
	bic r1, #7
	orr r1, #1
	@Commented out so we stick with TTBR0 for now
	@mcr p15, 0, r1, c2, c0, 2

	@Identity map the first 1MB.
	mov r1, #0x2
	@r0 should still hold =.p_root_page_table
	@TODO: reload anyway? (to prevent future bugs from emerging)
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
	mov r0, #max_phys_pages
	mov r1, #0x12
	ldr r2, =(.p_root_page_table + (4096 - max_phys_pages) * 4)
	.map_phys:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_phys
	

	@Map the I/O area.
	@To do: implement mapping multiple pages.
	ldr r1, =(phys_io_base + 0x12)
	ldr r2, =(.p_root_page_table + ((4096 - max_phys_pages - 1) * 4))
	str r1, [r2]
	
	@Set domain 0 to have no access restrictions.
	mov r0, #0x3
	mcr p15, 0, r0, c3, c0, 0

	.global test_1
	test_1:

	@Enable the MMU.
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x1
	mcr p15, 0, r0, c1, c0, 0

	@Restore bootloader parameters.
	ldmia sp!, {r0-r2}

	@Enter kmain.
	add lr, pc, #0x4
	ldr pc, =kmain
	
	.loop:
	b .loop

.section .text
.align 2

@TODO: remove?
.section .data
@16KB aligned
.align 12

