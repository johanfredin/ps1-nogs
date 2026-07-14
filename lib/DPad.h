/*
 * Wrapper for handling basic dpad controls. Uses player 1 only currently.
 * This lib uses only the standard libetc functions and does not work with anything else than
 * the digital pad
 */
#ifndef PSX_DEV_DPAD_H
#define PSX_DEV_DPAD_H

#define DPAD_PLAYER_1 1
#define DPAD_P1_INTERACT PADstart
#include <stdint.h>

typedef struct DPad {
    int32_t id;
    uint32_t curr_btn;
} DPad;

/**
 * Allocates space for Controller on the heap and sets id to passed in param.
 * @return ptr to new controller
 */
DPad *DPad_Init();

#define DPAD_READ_INPUT(controller) (controller)->curr_btn = PadRead(DPAD_PLAYER_1)
#define DPAD_DPAD_UP(controller) ((controller)->curr_btn & PADLup)
#define DPAD_DPAD_DOWN(controller) ((controller)->curr_btn & PADLdown)
#define DPAD_DPAD_LEFT(controller) ((controller)->curr_btn & PADLleft)
#define DPAD_DPAD_RIGHT(controller) ((controller)->curr_btn & PADLright)
#define DPAD_BTN_INTERACT(controller) ((controller)->curr_btn & DPAD_P1_INTERACT)


#endif //PSX_DEV_DPAD_H
