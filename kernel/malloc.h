#ifndef _MALLOC_H
#define _MALLOC_H

void* malloc(size_t size);
void free(void* ptr);
void realloc(void* ptr, size_t size);

#endif

