CFLAGS := --std=gnu99 -g -O2 -Wall

CC_PREFIX := arm-none-eabi
CC := $(CC_PREFIX)-gcc
AS := $(CC_PREFIX)-as
LD := $(CC_PREFIX)-ld
OBJCOPY := $(CC_PREFIX)-objcopy

find_files = $(wildcard $1) $(shell find platform/current -iname '$1')

C_SRC := $(call find_files,*.c)
C_H := $(call find_files,*.h)
C_OBJ := $(C_SRC:%.c=%.o)
ASM_SRC := $(call find_files,*.s)
ASM_OBJ := $(ASM_SRC:%.s=%.o)
OBJS := $(C_OBJ) $(ASM_OBJ)

kernel.img: kernel.elf
	$(OBJCOPY) $< -O binary $@ 

kernel.elf: $(OBJS)
	echo $(call find_files,*.c)
	$(LD) $^ -o $@ -T platform/current/kernel.ld
	
$(C_OBJ): %.o : %.c $(C_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ): %.o: %.s
	$(AS) $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

