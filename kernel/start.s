@Physically placed at 0x8000
.section .init
.align 2

@The bootloader puts root_page_table at this physical address.
.equ .p_root_page_table, (root_page_table - 0xC000000)

.global _start
_start:
	@Set up stack.
	mov sp, #0x8000
	
	@Store bootloader parameters.
	stmdb sp!, {r0-r2}
	
	@Set up paging:
	
	@Inform the MMU of the root page table's location.
	ldr r0, =.p_root_page_table
	mcr p15, 0, r0, c2, c0, 0

	@Identity map the first 1MB.
	mov r1, #0x2
	str r1, [r0]
	
	@Map the higher "half".
	mov r0, #8
	ldr r1, =0x2
	@This corresponds to the physical address 0xC0000000.
	ldr r2, =(.p_root_page_table + ((4096 - 1024) * 4))
	.map_upper:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_upper

	@Map the I/O area. (0x20000000 phys. => 0xF2000000 virt.)
	@To do: map fewer pages.
	mov r0, #112
	ldr r1, =0x20000002
	ldr r2, =(.p_root_page_table + ((4096 - 224) * 4))
	.map_io:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_io
	
	@Map the cache-coherent I/O area. (0x60000000 phys. => 0xF2000000 virt.)
	@To do: map fewer pages.
	mov r0, #112
	ldr r1, =0x60000002
	ldr r2, =(.p_root_page_table + ((4096 - 112) * 4))
	.map_io_cc:
		str r1, [r2]
		add r1, r1, #0x100000
		add r2, r2, #4
		subs r0, #1
		bne .map_io
	
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

.global error
error:
	b error

.section .data
@16KB aligned
.align 12

