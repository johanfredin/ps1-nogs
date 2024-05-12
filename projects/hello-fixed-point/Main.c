/*
 * Nothing that runs on the ps1, just messing around figuring out fixed point arithmetic
 */

#include <stdio.h>
#include <stdint.h>

#define SCALE 4

// 0000 . 0000

#define TO_FIXED(f) ((f) * (double)(1 << SCALE))

int main()
{
    uint8_t fixed = TO_FIXED(3.14);
    printf("To fixed=%d", fixed);

    return 0;
}
