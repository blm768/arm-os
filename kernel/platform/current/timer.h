#ifndef _TIMER_H
#define _TIMER_H

#include "../../common.h"

#include "memdef.h"

#define SYS_TIMER_CONTROL (*(uint*) (IO_BASE + 0x3000))
#define SYS_TIMER_VALUE   (*(ulong*)(IO_BASE + 0x3004))
#define SYS_TIMER_COMPARE (*(uint*) (IO_BASE + 0x300C))

#define SYS_TICKS_PER_SEC 1000000000

static inline bool sys_timer_triggered(uint timer) {
	return SYS_TIMER_CONTROL & (1 << timer);
}

static inline void acknowledge_sys_timer(uint timer) {
	//Counterintutively, the bit must be set to clear it.
	SYS_TIMER_CONTROL |= (1 << timer);
}

/////////////
//CPU timer//
/////////////

typedef enum {
	large_counter = 1 << 1,
	prescale_16 = 1 << 2,
	prescale_256 = 1 << 3, //Mutually exclusive with the above!
	enable_interrupt = 1 << 5,
	enable = 1 << 7,
	halt_in_debug = 1 << 8,
	enable_free_run = 1 << 9,
	free_run_prescale_1 = 1 << 16,
	prescale_reset = 0x3E0000,
} CPUTimerControl;

#define CPU_TIMER_SET     (*(volatile uint*)(IO_BASE + 0xB400))
#define CPU_TIMER_VALUE   (*(volatile uint*)(IO_BASE + 0xB404))
#define CPU_TIMER_CONTROL (*(volatile CPUTimerControl*)(IO_BASE + 0xB408))
#define CPU_TIMER_ACK     (*(volatile uint*)(IO_BASE + 0xB40C))
#define CPU_TIMER_STATUS  (*(volatile uint*)(IO_BASE + 0xB410))
#define CPU_TIMER_RESET   (*(volatile uint*)(IO_BASE + 0xB418))
#define CPU_TIMER_PREDIV  (*(volatile uint*)(IO_BASE + 0xB41C))

#define CPU_TIMER_PREDIV_DEFAULT 249

static inline void cpu_timer_set(uint value) {
	CPU_TIMER_CONTROL = prescale_reset;
	CPU_TIMER_SET = value;
	CPU_TIMER_RESET = value;
	CPU_TIMER_PREDIV = CPU_TIMER_PREDIV_DEFAULT;
	CPU_TIMER_ACK = 1;
	CPU_TIMER_CONTROL = prescale_reset | large_counter;
}

static inline void cpu_timer_start() {
	CPU_TIMER_CONTROL |= enable;
}

static inline void cpu_timer_stop() {
	CPU_TIMER_CONTROL &= ~enable;
}

//Only enables interrupts on the timer side
static inline void cpu_timer_enable_interrupt() {
	CPU_TIMER_CONTROL |= enable_interrupt;
}

static inline void cpu_timer_ack() {
	CPU_TIMER_ACK = 1;
}

static inline bool cpu_timer_done() {
	return (bool)CPU_TIMER_STATUS;
}

#endif
