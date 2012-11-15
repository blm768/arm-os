C_SRC := $(shell find . -iname '*.c')
C_H := $(shell find . -iname '*.h')
C_OBJ := $(C_SRC:%.c=%.o) 
OBJS := $(C_OBJ) start.o

kernel.img: kernel.elf
	arm-none-eabi-objcopy $< -O binary $@ 

kernel.elf: $(OBJS)
	arm-none-eabi-ld $? -o $@ -T kernel.ld

$(C_OBJ): %.o : %.c $(C_H) start.s
	arm-none-eabi-gcc --std=gnu99 -g -c $< -o $@

start.o: start.s
	arm-none-eabi-as start.s -o start.o	