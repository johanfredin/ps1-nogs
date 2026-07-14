/*
 * Wrapper for handling controller input from a digital, analog and dual shock controllers. More flexible than Dpad lib.
 * Most of the stuff written here have been taken from the awesome Lameguy tutorials at http://rsync.irixnet.org/tutorials/pstutorials/chapter1/4-controllers.html
 */
#ifndef PSX_DEV_CONTROLLER_H
#define PSX_DEV_CONTROLLER_H

#define NUM_CONTROLLERS 2
#define PAD_BUFF_SIZE 34

#define CONTROLLER_PAD_1 0
#define CONTROLLER_PAD_2 1

#define CONTROLLER_STAT_CONNECTED 0
#define CONTROLLER_TYPE_MOUSE 0x1
#define CONTROLLER_TYPE_NAMCO_NEGCON 0x2
#define CONTROLLER_TYPE_DIGITAL 0x4
#define CONTROLLER_TYPE_ANALOG 0x5
#define CONTROLLER_TYPE_DUAL_SHOCK 0x7
#define CONTROLLER_TYPE_NAMCO_JOCCON 0xE

#define CONTROLLER_IS_CONNECTED(controller) (controller)->stat == CONTROLLER_STAT_CONNECTED

#define CONTROLLER_BTN_SELECT      1
#define CONTROLLER_BTN_L3          2
#define CONTROLLER_BTN_R3          4
#define CONTROLLER_BTN_START       8
#define CONTROLLER_BTN_UP          16
#define CONTROLLER_BTN_RIGHT       32
#define CONTROLLER_BTN_DOWN        64
#define CONTROLLER_BTN_LEFT        128
#define CONTROLLER_BTN_L2          256
#define CONTROLLER_BTN_R2          512
#define CONTROLLER_BTN_L1          1024
#define CONTROLLER_BTN_R1          2048
#define CONTROLLER_BTN_TRIANGLE    4096
#define CONTROLLER_BTN_CIRCLE      8192
#define CONTROLLER_BTN_CROSS       16384
#define CONTROLLER_BTN_SQUARE      32768

#define CONTROLLER_NO_INPUT(ctrl) (ctrl)->curr_btn & 0xffff

#define CONTROLLER_IS_BTN_SELECT(controller) !((controller)->curr_btn & CONTROLLER_BTN_SELECT)
#define CONTROLLER_IS_BTN_L3(controller) !((controller)->curr_btn & CONTROLLER_BTN_L3)
#define CONTROLLER_IS_BTN_R3(controller) !((controller)->curr_btn & CONTROLLER_BTN_R3)
#define CONTROLLER_IS_BTN_START(controller) !((controller)->curr_btn & CONTROLLER_BTN_START)
#define CONTROLLER_IS_BTN_UP(controller) !((controller)->curr_btn & CONTROLLER_BTN_UP)
#define CONTROLLER_IS_BTN_RIGHT(controller) !((controller)->curr_btn & CONTROLLER_BTN_RIGHT)
#define CONTROLLER_IS_BTN_LEFT(controller) !((controller)->curr_btn & CONTROLLER_BTN_LEFT)
#define CONTROLLER_IS_BTN_DOWN(controller) !((controller)->curr_btn & CONTROLLER_BTN_DOWN)
#define CONTROLLER_IS_BTN_L2(controller) !((controller)->curr_btn & CONTROLLER_BTN_L2)
#define CONTROLLER_IS_BTN_R2(controller) !((controller)->curr_btn & CONTROLLER_BTN_R2)
#define CONTROLLER_IS_BTN_L1(controller) !((controller)->curr_btn & CONTROLLER_BTN_L1)
#define CONTROLLER_IS_BTN_R1(controller) !((controller)->curr_btn & CONTROLLER_BTN_R1)
#define CONTROLLER_IS_BTN_TRIANGLE(controller) !((controller)->curr_btn & CONTROLLER_BTN_TRIANGLE)
#define CONTROLLER_IS_BTN_CIRCLE(controller) !((controller)->curr_btn & CONTROLLER_BTN_CIRCLE)
#define CONTROLLER_IS_BTN_CROSS(controller) !((controller)->curr_btn & CONTROLLER_BTN_CROSS)
#define CONTROLLER_IS_BTN_SQUARE(controller) !((controller)->curr_btn & CONTROLLER_BTN_SQUARE)

#define CONTROLLER_P1_INTERACT CONTROLLER_BTN_START

#define CONTROLLER_READ_P1() CONTROLLER_read(CONTROLLER_PAD_1)

#define CONTROLLER_LOG_INPUT(pad)                             \
    char *current_button = "";                          \
    uint8_t is_connected = CONTROLLER_IS_CONNECTED(pad);       \
    if (is_connected) {                                 \
        char *type = "";                                \
        switch (pad->type) {                            \
            case CONTROLLER_TYPE_DIGITAL:                     \
                type = "Digital";                       \
                break;                                  \
            case CONTROLLER_TYPE_ANALOG:                      \
                type = "Analog";                        \
                FntPrint("Sticks stat L3 (x,y), R3=(x, y),(%d,%d), (%d, %d)\n", pad->ls_x, pad->ls_y, pad->rs_x, pad->rs_y);    \
                break;                                                                                                          \
            case CONTROLLER_TYPE_DUAL_SHOCK:                                                                                          \
                type = "Dual Shock";                                                                                            \
                FntPrint("Sticks stat L3 (x,y), R3=(x, y),(%d,%d), (%d, %d)\n", pad->ls_x, pad->ls_y, pad->rs_x, pad->rs_y);    \
                break;                                                                                                          \
            default:                                                                                                            \
                type = "UNKNOWN";                                                                                               \
        }                                                                                                                       \
        FntPrint("Controller type=%s\n", type);                                                                                                                                                                       \
        if (CONTROLLER_IS_BTN_UP(pad)) { current_button = "UP"; }                             \
        if (CONTROLLER_IS_BTN_DOWN(pad)) { current_button = "DOWN"; }                         \
        if (CONTROLLER_IS_BTN_LEFT(pad)) { current_button = "LEFT"; }                         \
        if (CONTROLLER_IS_BTN_RIGHT(pad)) { current_button = "RIGHT"; }                       \
        if (CONTROLLER_IS_BTN_CROSS(pad)) { current_button = "X"; }                           \
        if (CONTROLLER_IS_BTN_SQUARE(pad)) { current_button = "[]"; }                         \
        if (CONTROLLER_IS_BTN_CIRCLE(pad)) { current_button = "()"; }                         \
        if (CONTROLLER_IS_BTN_TRIANGLE(pad)) { current_button = "/\\"; }                      \
        if (CONTROLLER_IS_BTN_START(pad)) { current_button = "START"; }                       \
        if (CONTROLLER_IS_BTN_SELECT(pad)) { current_button = "SELECT"; }                     \
        if (CONTROLLER_IS_BTN_R1(pad)) { current_button = "R1"; }                             \
        if (CONTROLLER_IS_BTN_R2(pad)) { current_button = "R2"; }                             \
        if (CONTROLLER_IS_BTN_L1(pad)) {current_button = "L1";  }                             \
        if (CONTROLLER_IS_BTN_L2(pad)) { current_button = "L2"; }                             \
        if (CONTROLLER_IS_BTN_R3(pad)) { current_button = "R3"; }                             \
        if (CONTROLLER_IS_BTN_L3(pad)) { current_button = "L3"; }                             \
    }                                                                                   \
    FntPrint("Connected=%d\nButton pressed=%s", is_connected, current_button)
#include <stdint.h>


typedef struct Controller {
    // Status of controller 0 = connected, 1 = not connected
    uint8_t stat;
    uint8_t len: 4;
    // The controller type (dual-shock, standard etc.)
    uint8_t type: 4;
    // The current btn pressed
    uint16_t curr_btn;
    uint8_t rs_x, rs_y;  // right analog stick x,y
    uint8_t ls_x, ls_y;  // left analog stick x,y
} Controller;

/**
 * Allocates space for Controller on the heap and sets id to passed in param.
 * @param id controller id (0=Player 1)
 * @return ptr to new controller
 */
Controller *Controller_Read(uint8_t id);
void Controller_Init(void);

#endif //PSX_DEV_CONTROLLER_H
