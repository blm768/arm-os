CFLAGS := --std=gnu99 -g -O2 -Wall

find_files = $(wildcard $1) $(shell find platform/current -iname '$1')

C_SRC := $(call find_files,*.c)
C_H := $(call find_files,*.h)
C_OBJ := $(C_SRC:%.c=%.o)
ASM_SRC := $(call find_files,*.s)
ASM_OBJ := $(ASM_SRC:%.s=%.o)
OBJS := $(C_OBJ) $(ASM_OBJ)

kernel.img: kernel.elf
	arm-none-eabi-objcopy $< -O binary $@ 

kernel.elf: $(OBJS)
	echo $(call find_files,*.c)
	arm-none-eabi-ld $^ -o $@ -T platform/current/kernel.ld
	
$(C_OBJ): %.o : %.c $(C_H)
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

$(ASM_OBJ): %.o: %.s
	arm-none-eabi-as $< -o $@

.PHONY: clean

clean:
	rm -rf obj kernel.img kernel.elf $(shell find -iname '*.o')

