include platform/current/use.mak

COMPILE_FLAGS += -g
CFLAGS += $(COMPILE_FLAGS) -I.
CFLAGS += --std=gnu99 -Wall
ASFLAGS += $(COMPILE_FLAGS)

CC_PREFIX := arm-none-eabi-
CC := $(CC_PREFIX)gcc
AS := $(CC_PREFIX)as
LD := $(CC_PREFIX)ld
OBJCOPY := $(CC_PREFIX)objcopy

src_dirs = $(components:%=components/%) platform/current cpu/current

find_files = $(wildcard $1) $(foreach dir, $(src_dirs), $(shell find -H $(dir) -iname '$1'))

c_src := $(call find_files,*.c)
c_h := $(call find_files,*.h)
c_obj := $(c_src:%.c=%.o)
asm_src := $(call find_files,*.s)
asm_obj := $(asm_src:%.s=%_asm.o)
asm_inc := $(call find_files,*.s.inc)
objs := $(c_obj) $(asm_obj)

kernel.img: kernel.elf
	$(OBJCOPY) $< -O binary $@

kernel.elf: $(objs)
	$(LD) $^ -o $@ -T platform/current/kernel.ld
	
$(c_obj): %.o : %.c $(c_h)
	$(CC) $(CFLAGS) -c $< -o $@

$(asm_obj): %_asm.o: %.s $(asm_inc)
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

