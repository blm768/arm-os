#ifndef _CPU_THREAD_H
#define _CPU_THREAD_H

typedef struct {
	size_t pid;
	union {
		size_t registers[16];
		struct {
			size_t gprs[14];
			size_t sp;
			size_t lr;
			size_t pc;
		};
	};
} Thread;

#endif

