C_SRC := $(shell find . -iname '*.c')
C_H := $(shell find . -iname '*.h')
C_OBJ := $(C_SRC:%.c=%.o) 
OBJS := $(C_OBJ) start.o

kernel.bin: kernel.elf
	arm-none-eabi-objcopy $< -O binary $@ 

kernel.elf: $(OBJS)
	arm-none-eabi-ld $? -o $@ -T kernel.ld

start.o: start.s
	arm-none-eabi-as start.s -o start.o

$(C_OBJ): %.o : %.c $(C_H) start.s
	arm-none-eabi-gcc --std=gnu99 -c $< -o $@ 