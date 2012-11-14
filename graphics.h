#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "common.h"

typedef struct {
	int width, height;
	int vWidth, vHeight;
	int pitch, depth;
	int x, y;
	void* buffer;
	uint size;
} FramebufferInfo;

#define MAIL_RECV (*(int*)0x2000B880)
#define MAIL_SEND (*(int*)0x2000B8A0)
#define MAIL_STATUS (*(int*)0x2000B898)

static inline int get_send_status() {
	return MAIL_STATUS & (1 << 31);
};

static inline bool send_message(int mBox, int msg) {
	while(get_send_status()) {}
	MAIL_SEND = mBox | (msg << 4);
}

static inline int get_recv_status() {
	return MAIL_STATUS & (1 << 30);
}

static inline int recv_message(int mBox) {
	while(get_recv_status()) {}
	//To do: check that this is the right mailbox.
	return 0;
	//return MAIL_RECV >> 4;
}

#endif
