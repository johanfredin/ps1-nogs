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
    void *p = malloc3(n);
    if (p == NULL) {
        logr_log(ERROR, "Heap.c", "heap_malloc", "Null ptr returned from malloc, terminating...");
        exit(1);
    }
    return p;
}

void *heap_calloc(size_t n, size_t s) {
    void *p = calloc3(n, s);
    if (p == NULL) {
        logr_log(ERROR, "Heap.c", "heap_calloc", "Null ptr returned from calloc, terminating...");
        exit(1);
    }
    return p;
}

void heap_free(void *ptr) {
    if (ptr == NULL) {
        logr_log(ERROR, "Heap.c", "heap_free", "Attempted to free a NULL ptr, terminating...");
        exit(1);
    }
    free3(ptr);
    ptr = NULL;
}
