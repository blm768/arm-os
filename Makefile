C_SRC := $(shell find . -iname '*.c')
C_H := $(shell find . -iname '*.h')
C_OBJ := $(C_SRC:%.c=%.o)
ASM_SRC := $(shell find . -iname '*.s')
ASM_OBJ := $(ASM_SRC:%.s=%.o)
OBJS := $(C_OBJ) $(ASM_OBJ)

kernel.img: kernel.elf
	arm-none-eabi-objcopy $< -O binary $@ 

kernel.elf: $(OBJS)
	arm-none-eabi-ld $? -o $@ -T kernel.ld
	
$(C_OBJ): %.o : %.c $(C_H)
	arm-none-eabi-gcc --std=gnu99 -g -c $< -o $@

$(ASM_OBJ): %.o: %.s
	arm-none-eabi-as $< -o $@
