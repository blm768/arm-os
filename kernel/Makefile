include platform/current/use.mak
include cpu/current/use.mak

CFLAGS += -I.
CFLAGS += --std=gnu99 -g -O2 -Wall

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
objs := $(c_obj) $(asm_obj)

kernel.img: kernel.elf
	$(OBJCOPY) $< -O binary $@

kernel.elf: $(objs)
	$(LD) $^ -o $@ -T platform/current/kernel.ld
	
$(c_obj): %.o : %.c $(C_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(asm_obj): %_asm.o: %.s
	$(AS) $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

