//
// Created by johan on 2024-04-07.
//

#include "Heap.h"
#include "Log.h"
#include <malloc.h>

#include "stdio.h"

void Heap_Init(void) {
    InitHeap3((unsigned long *) HEAP_START_ADDR, HEAP_SIZE); \
    LOG_INFO("Heap initialized. Start addr=%X, heap size=%X", HEAP_START_ADDR, HEAP_SIZE);
}

void *Heap_Malloc(const size_t n) {
    void *p = calloc3(1,n);
    if (!p) {
        LOG_ERR("Null ptr returned from malloc, terminating...");
        exit(1);
    }
    return p;
}

void *Heap_Calloc(const size_t n, const size_t s) {
    void *p = calloc3(n, s);
    if (p == NULL) {
        LOG_ERR("Null ptr returned from calloc, terminating...");
        exit(1);
    }
    return p;
}

void Heap_Free(void *ptr) {
    if (ptr == NULL) {
        LOG_ERR("Attempted to free a NULL ptr, terminating...");
        exit(1);
    }
    free3(ptr);
    ptr = NULL;
}
