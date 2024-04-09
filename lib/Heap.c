//
// Created by johan on 2024-04-07.
//

#include "Heap.h"
#include "Logger.h"
#include <malloc.h>

void heap_init() {
    InitHeap3((unsigned long *) HEAP_START_ADDR, HEAP_SIZE); \
    logr_log(INFO, "MemUtils.c", "MEM_INIT_HEAP_3", "ROM heap initialized. Start addr=%X, heap size=%X",
             HEAP_START_ADDR, HEAP_SIZE);
}

void *heap_malloc(size_t n) {
    return malloc3(n);
}

void *heap_calloc(size_t n, size_t s) {
    return calloc3(n, s);
}

void heap_free(void *ptr) {
    if (ptr != NULL) {
        free3(ptr);
        ptr = NULL;
    }
}
