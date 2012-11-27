#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

#define SYS_TIMER_CONTROL (*(uint*)0x20003000)
#define SYS_TIMER_VALUE   (*(ulong*)0x20003004)
#define SYS_TIMER_COMPARE (*(uint*)0x2000300C)

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
} CPUTimerControl;

#define CPU_TIMER_COMPARE (*(uint*)0x2000B400)
#define CPU_TIMER_VALUE   (*(uint*)0x2000B404)
#define CPU_TIMER_CONTROL (*(CPUTimerControl*)0x2000B408)
#define CPU_TIMER_ACK     (*(uint*)0X2000B40C)

static inline void enable_cpu_timer() {
	CPU_TIMER_CONTROL |= enable;
}

//Only enables interrupts on the timer side
static inline void enable_cpu_timer_interrupt() {
	CPU_TIMER_CONTROL |= enable_interrupt;
}

static inline void acknowledge_cpu_timer() {
	CPU_TIMER_ACK = 1;
}

#endif
