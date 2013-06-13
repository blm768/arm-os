.global data_memory_barrier
data_memory_barrier:
	dmb
	bx lr

@Standard memory barrier for peripheral access
@http://www.raspberrypi.org/phpBB3/viewtopic.php?t=5847&p=99724
.global peripheral_memory_barrier
peripheral_memory_barrier:
	mcr p15, 0, ip, c7, c5, 0
	mcr p15, 0, ip, c7, c5, 6
	mcr p15, 0, ip, c7, c10, 4
	mcr p15, 0, ip, c7, c5, 4
	bx lr
