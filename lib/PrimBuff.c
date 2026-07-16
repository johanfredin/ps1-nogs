//
// Created by johan on 2026-07-16.
//

#include "PrimBuff.h"

static char buff[2][PRIM_BUFF_CAPACITY];
static char *next_prim;

void PrimBuff_Clear(const uint8_t current_buffer) {
    next_prim = buff[current_buffer];
}

void *PrimBuff_AcquireSlot(const size_t prim_size) {
    void *slot = next_prim;
    next_prim += prim_size;
    return slot;
}

