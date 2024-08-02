//
// Created by johan on 2024-02-28.
//

#ifndef PS1_DEV_ANIMATION_H
#define PS1_DEV_ANIMATION_H

#include <sys/types.h>

typedef struct Animation {
    u_char cols:5;
    u_char rows:3;
    u_char curr_col:5;
    u_char curr_row:3;
    u_char start_row;
    u_char ticks_per_frame;
    u_char acc_ticks;
} Animation;

void anim_init(Animation *animation, u_char cols, u_char rows, u_char ticks_per_frame, u_char start_row);

/**
 * Update passed in object with current animation state
 * @param anim animation object that will update image of passed in game object
 */
Animation *anim_tick(Animation *anim);

#endif //PS1_DEV_ANIMATION_H
