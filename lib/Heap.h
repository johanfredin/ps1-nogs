//
// Created by johan on 2024-04-07.
//

#ifndef PS1_DEV_HEAP_H
#define PS1_DEV_HEAP_H

#include "stdlib.h"

#define HEAP_START_ADDR 0x800F8000
#define HEAP_SIZE 0x00100000            // 1 mb heap

void heap_init();
void *heap_malloc(size_t n);
void *heap_calloc(size_t n, size_t s);
void heap_free(void *ptr);


#endif //PS1_DEV_HEAP_H
