#ifndef PS1_DEV_PRIMBUFF_H
#define PS1_DEV_PRIMBUFF_H

#define PRIM_BUFF_CAPACITY 2048
#include <stdint.h>

#include "types.h"

void PrimBuff_Clear(uint8_t current_buffer);
void *PrimBuff_AcquireSlot(size_t prim_size);

#endif //PS1_DEV_PRIMBUFF_H
