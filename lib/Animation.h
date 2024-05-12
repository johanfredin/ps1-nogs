//
// Created by johan on 2024-02-28.
//

#ifndef PS1_DEV_ANIMATION_H
#define PS1_DEV_ANIMATION_H

#include <stdint-gcc.h>

typedef struct Animation {
    uint8_t cols:5;
    uint8_t rows:3;
    uint8_t curr_col:5;
    uint8_t curr_row:3;
    uint8_t start_row;
    uint8_t ticks_per_frame;
    uint8_t acc_ticks;
} Animation;

void anim_init(Animation *animation, uint8_t cols, uint8_t rows, uint8_t ticks_per_frame, uint8_t start_row);

/**
 * Update passed in object with current animation state
 * @param anim animation object that will update image of passed in game object
 */
Animation *anim_tick(Animation *anim);

#endif //PS1_DEV_ANIMATION_H
