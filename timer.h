#ifndef _TIMER_H
#define _TIMER_H

#include "common.h"

#define TIMER_CONTROL (*(uint*)0x20003000)
#define TIMER_VALUE   (*(ulong*)0x20003004)
#define TIMER_TRIGGER (*(uint*)0x2000300C)

#define TICKS_PER_SEC 1000000000

static inline bool timer_triggered(uint timer) {
	return TIMER_CONTROL & (1 << timer);
}

static inline void acknowledge_timer(uint timer) {
	//Counterintutively, the bit must be set to clear it.
	TIMER_CONTROL |= (1 << timer);
}

#endif
