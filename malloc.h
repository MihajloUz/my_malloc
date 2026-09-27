#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stddef.h>

void *mmalloc(size_t size);
void mfree(void* addr);

#endif
