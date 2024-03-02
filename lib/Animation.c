//
// Created by johan on 2024-02-28.
//

#include "Animation.h"
#include "Logger.h"

void anim_init(Animation *animation, uint8_t cols, uint8_t rows, uint8_t ticks_per_frame, uint8_t start_row) {
    animation->cols = cols;
    animation->rows = rows;
    animation->ticks_per_frame = ticks_per_frame;
    animation->acc_ticks = 0;
    animation->curr_col = 0;
    animation->curr_row = start_row;
    animation->start_row = start_row;
}

Animation *anim_tick(Animation *anim) {
    uint8_t curr_col = anim->curr_col;
    uint8_t curr_row = anim->curr_row;
    uint8_t acc_ticks = anim->acc_ticks;

    if (acc_ticks >= anim->ticks_per_frame) {
        if (curr_col >= anim->cols) {
            curr_col = 0;
            curr_row++;
            if (anim->curr_row >= (anim->rows) - 1) {
                curr_row = anim->start_row;
            }
        } else {
            curr_col++;
        }
        acc_ticks = 0;
    } else {
        acc_ticks++;
    }

    // Update the passed in animation
    anim->curr_row = curr_row;
    anim->curr_col = curr_col;
    anim->acc_ticks = acc_ticks;
    logr_log(TRACE, "Animation.c", "anim_tick", "curr-row=%d, curr_col=%d, acc_ticks=%d", anim->curr_row, anim->curr_col,
             anim->acc_ticks);

    return anim;
}