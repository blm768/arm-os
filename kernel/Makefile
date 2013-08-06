CFLAGS += -I.
CFLAGS += --std=gnu99 -g -O2 -Wall

CC_PREFIX := arm-eabi-
CC := $(CC_PREFIX)gcc
AS := $(CC_PREFIX)as
LD := $(CC_PREFIX)ld
OBJCOPY := $(CC_PREFIX)objcopy

find_files = $(wildcard $1) $(shell find platform/current -iname '$1') $(shell find cpu/current -iname '$1')

c_src := $(call find_files,*.c)
c_h := $(call find_files,*.h)
c_obj := $(c_src:%.c=%.o)
asm_src := $(call find_files,*.s)
asm_obj := $(asm_src:%.s=%.o)
objs := $(c_obj) $(asm_obj)

kernel.img: kernel.elf
	$(OBJCOPY) $< -O binary $@

kernel.elf: $(objs)
	echo $(call find_files,*.c)
	$(LD) $^ -o $@ -T platform/current/kernel.ld
	
$(c_obj): %.o : %.c $(C_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(asm_obj): %.o: %.s
	$(AS) $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

