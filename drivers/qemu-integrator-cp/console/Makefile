COMPILE_FLAGS += -g
CFLAGS += $(COMPILE_FLAGS) -I. -fpic
CFLAGS += --std=gnu99 -Wall
ASFLAGS += $(COMPILE_FLAGS)

CC_PREFIX := arm-none-eabi-
CC := $(CC_PREFIX)gcc
AS := $(CC_PREFIX)as
LD := $(CC_PREFIX)ld
OBJCOPY := $(CC_PREFIX)objcopy

find_files = $(wildcard $1)

c_src := $(call find_files,*.c)
c_h := $(call find_files,*.h)
c_obj := $(c_src:%.c=%.o)
asm_src := $(call find_files,*.s) ../start.s
asm_obj := $(asm_src:%.s=%_asm.o)
asm_inc := $(call find_files,*.s.inc)
objs := $(c_obj) $(asm_obj)

console.elf: $(objs)
	$(LD) $^ -o $@
	
$(c_obj): %.o : %.c $(c_h)
	$(CC) $(CFLAGS) -c $< -o $@

$(asm_obj): %_asm.o: %.s $(asm_inc)
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

