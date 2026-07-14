//
// Created by johan on 2024-04-07.
//

#include "Heap.h"
#include "Logger.h"
#include <malloc.h>

void Heap_Init(void) {
    InitHeap3((unsigned long *) HEAP_START_ADDR, HEAP_SIZE); \
    logr_log(INFO, "MemUtils.c", "MEM_INIT_HEAP_3", "ROM heap initialized. Start addr=%X, heap size=%X",
             HEAP_START_ADDR, HEAP_SIZE);
}

void *Heap_Malloc(const size_t n) {
    void *p = calloc3(1,n);
    if (p == NULL) {
        logr_log(ERROR, "Heap.c", "heap_malloc", "Null ptr returned from malloc, terminating...");
        exit(1);
    }
    return p;
}

void *Heap_Calloc(const size_t n, const size_t s) {
    void *p = calloc3(n, s);
    if (p == NULL) {
        logr_log(ERROR, "Heap.c", "heap_calloc", "Null ptr returned from calloc, terminating...");
        exit(1);
    }
    return p;
}

void Heap_Free(void *ptr) {
    if (ptr == NULL) {
        logr_log(ERROR, "Heap.c", "heap_free", "Attempted to free a NULL ptr, terminating...");
        exit(1);
    }
    free3(ptr);
    ptr = NULL;
}
