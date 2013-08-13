#ifndef _CPU_THREAD_H
#define _CPU_THREAD_H

typedef struct {
	size_t pid;
	union {
		size_t registers[16];
	};
} Thread;

#endif

