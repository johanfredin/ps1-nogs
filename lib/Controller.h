/*
 * Wrapper for handling controller input from a digital, analog and dual shock controllers. More flexible than Dpad lib.
 * Most of the stuff written here have been taken from the awesome Lameguy tutorials at http://rsync.irixnet.org/tutorials/pstutorials/chapter1/4-controllers.html
 */
#ifndef PSX_DEV_CONTROLLER_H
#define PSX_DEV_CONTROLLER_H

#define NUM_CONTROLLERS 2
#define PAD_BUFF_SIZE 34

#define CTRL_PAD_1 0
#define CTRL_PAD_2 1

#define CTRL_STAT_CONNECTED 0
#define CTRL_TYPE_MOUSE 0x1
#define CTRL_TYPE_NAMCO_NEGCON 0x2
#define CTRL_TYPE_DIGITAL 0x4
#define CTRL_TYPE_ANALOG 0x5
#define CTRL_TYPE_DUAL_SHOCK 0x7
#define CTRL_TYPE_NAMCO_JOCCON 0xE

#define CTRL_IS_CONNECTED(controller) (controller)->stat == CTRL_STAT_CONNECTED

#define CTRL_BTN_SELECT      1
#define CTRL_BTN_L3          2
#define CTRL_BTN_R3          4
#define CTRL_BTN_START       8
#define CTRL_BTN_UP          16
#define CTRL_BTN_RIGHT       32
#define CTRL_BTN_DOWN        64
#define CTRL_BTN_LEFT        128
#define CTRL_BTN_L2          256
#define CTRL_BTN_R2          512
#define CTRL_BTN_L1          1024
#define CTRL_BTN_R1          2048
#define CTRL_BTN_TRIANGLE    4096
#define CTRL_BTN_CIRCLE      8192
#define CTRL_BTN_CROSS       16384
#define CTRL_BTN_SQUARE      32768

#define CTRL_NO_INPUT(ctrl) (ctrl)->curr_btn & 0xffff

#define CTRL_IS_BTN_SELECT(controller) !((controller)->curr_btn & CTRL_BTN_SELECT)
#define CTRL_IS_BTN_L3(controller) !((controller)->curr_btn & CTRL_BTN_L3)
#define CTRL_IS_BTN_R3(controller) !((controller)->curr_btn & CTRL_BTN_R3)
#define CTRL_IS_BTN_START(controller) !((controller)->curr_btn & CTRL_BTN_START)
#define CTRL_IS_BTN_UP(controller) !((controller)->curr_btn & CTRL_BTN_UP)
#define CTRL_IS_BTN_RIGHT(controller) !((controller)->curr_btn & CTRL_BTN_RIGHT)
#define CTRL_IS_BTN_LEFT(controller) !((controller)->curr_btn & CTRL_BTN_LEFT)
#define CTRL_IS_BTN_DOWN(controller) !((controller)->curr_btn & CTRL_BTN_DOWN)
#define CTRL_IS_BTN_L2(controller) !((controller)->curr_btn & CTRL_BTN_L2)
#define CTRL_IS_BTN_R2(controller) !((controller)->curr_btn & CTRL_BTN_R2)
#define CTRL_IS_BTN_L1(controller) !((controller)->curr_btn & CTRL_BTN_L1)
#define CTRL_IS_BTN_R1(controller) !((controller)->curr_btn & CTRL_BTN_R1)
#define CTRL_IS_BTN_TRIANGLE(controller) !((controller)->curr_btn & CTRL_BTN_TRIANGLE)
#define CTRL_IS_BTN_CIRCLE(controller) !((controller)->curr_btn & CTRL_BTN_CIRCLE)
#define CTRL_IS_BTN_CROSS(controller) !((controller)->curr_btn & CTRL_BTN_CROSS)
#define CTRL_IS_BTN_SQUARE(controller) !((controller)->curr_btn & CTRL_BTN_SQUARE)

#define CTRL_P1_INTERACT CTRL_BTN_START

#define CTRL_READ_P1() ctrl_read(CTRL_PAD_1)

#define CTRL_LOG_INPUT(pad)                             \
    char *current_button = "";                          \
    u_char is_connected = CTRL_IS_CONNECTED(pad);       \
    if (is_connected) {                                 \
        char *type = "";                                \
        switch (pad->type) {                            \
            case CTRL_TYPE_DIGITAL:                     \
                type = "Digital";                       \
                break;                                  \
            case CTRL_TYPE_ANALOG:                      \
                type = "Analog";                        \
                FntPrint("Sticks stat L3 (x,y), R3=(x, y),(%d,%d), (%d, %d)\n", pad->ls_x, pad->ls_y, pad->rs_x, pad->rs_y);    \
                break;                                                                                                          \
            case CTRL_TYPE_DUAL_SHOCK:                                                                                          \
                type = "Dual Shock";                                                                                            \
                FntPrint("Sticks stat L3 (x,y), R3=(x, y),(%d,%d), (%d, %d)\n", pad->ls_x, pad->ls_y, pad->rs_x, pad->rs_y);    \
                break;                                                                                                          \
            default:                                                                                                            \
                type = "UNKNOWN";                                                                                               \
        }                                                                                                                       \
        FntPrint("Controller type=%s\n", type);                                                                                                                                                                       \
        if (CTRL_IS_BTN_UP(pad)) { current_button = "UP"; }                             \
        if (CTRL_IS_BTN_DOWN(pad)) { current_button = "DOWN"; }                         \
        if (CTRL_IS_BTN_LEFT(pad)) { current_button = "LEFT"; }                         \
        if (CTRL_IS_BTN_RIGHT(pad)) { current_button = "RIGHT"; }                       \
        if (CTRL_IS_BTN_CROSS(pad)) { current_button = "X"; }                           \
        if (CTRL_IS_BTN_SQUARE(pad)) { current_button = "[]"; }                         \
        if (CTRL_IS_BTN_CIRCLE(pad)) { current_button = "()"; }                         \
        if (CTRL_IS_BTN_TRIANGLE(pad)) { current_button = "/\\"; }                      \
        if (CTRL_IS_BTN_START(pad)) { current_button = "START"; }                       \
        if (CTRL_IS_BTN_SELECT(pad)) { current_button = "SELECT"; }                     \
        if (CTRL_IS_BTN_R1(pad)) { current_button = "R1"; }                             \
        if (CTRL_IS_BTN_R2(pad)) { current_button = "R2"; }                             \
        if (CTRL_IS_BTN_L1(pad)) {current_button = "L1";  }                             \
        if (CTRL_IS_BTN_L2(pad)) { current_button = "L2"; }                             \
        if (CTRL_IS_BTN_R3(pad)) { current_button = "R3"; }                             \
        if (CTRL_IS_BTN_L3(pad)) { current_button = "L3"; }                             \
    }                                                                                   \
    FntPrint("Connected=%d\nButton pressed=%s", is_connected, current_button)


typedef struct Controller {
    // Status of controller 0 = connected, 1 = not connected
    unsigned char stat;
    unsigned char len: 4;
    // The controller type (dual-shock, standard etc.)
    unsigned char type: 4;
    // The current btn pressed
    unsigned short curr_btn;
    unsigned char rs_x, rs_y;  // right analog stick x,y
    unsigned char ls_x, ls_y;  // left analog stick x,y
} Controller;

/**
 * Allocates space for Controller on the heap and sets id to passed in param.
 * @param id controller id (0=Player 1)
 * @return ptr to new controller
 */
Controller *ctrl_read(unsigned char id);
void ctrl_init();

#endif //PSX_DEV_CONTROLLER_H
