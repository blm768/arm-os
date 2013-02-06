#ifndef _GPIO_H
#define _GPIO_H

#include "common.h"

#define GPIO_MODE  ((volatile uint*)0x20200000)
#define GPIO_SET   ((volatile uint*)0x2020001C)
#define GPIO_CLEAR ((volatile uint*)0x20200028)

/*
#define GPIO_MODE  ((volatile uint*)(IO_BASE + 0x200000))
#define GPIO_SET   ((volatile uint*)(IO_BASE + 0x20001C))
#define GPIO_CLEAR ((volatile uint*)(IO_BASE + 0x200028))
*/

void gpio_set_output(uint pin);
void gpio_set(uint pin);
void gpio_clear(uint pin);

#endif
