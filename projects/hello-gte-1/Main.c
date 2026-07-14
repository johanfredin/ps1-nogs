#include <libgpu.h>
#include <libgte.h>
#include <stdint.h>
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"

Controller *controller;
POLY_F3 space_ship;
SVECTOR v[3];

// For the player triangle
SVECTOR player_tri[3] = {
        {0,   -20, ONE  * 2},
        {10,  20, ONE * 2},
        {-10, 20, ONE * 2},
};

int32_t pos_x = ONE * (GPU_SCREEN_W >> 1);
int32_t pos_y = ONE * (GPU_SCREEN_H >> 1);

int angle = 0;
int scale = 1;

void check_pad();
void update_player_position();

int main() {
    // Initialize system
    GPU_Init();
    Controller_Init();

    GPU_InitPolyF3(&space_ship, player_tri, 255, 255, 0);

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        GPU_ClearOT();

        // Print player coordinates
        FntPrint("POS_X=%d (%d.%d)\n", pos_x, (pos_x>>12), (pos_x&0xfff) );
        FntPrint("POS_Y=%d (%d.%d)\n", pos_y, (pos_y>>12), (pos_y&0xfff) );
        FntPrint("ANGLE=%d, SCALE=%d\n", angle, scale);

        check_pad();
        update_player_position();

        // Add your update and draw function calls here
        GPU_SortPolyF3(&space_ship);

        GPU_Display();
    }
}

void check_pad() {
    controller = CONTROLLER_READ_P1();
    if (CONTROLLER_IS_CONNECTED(controller)) {
        if (CONTROLLER_IS_BTN_UP(controller)) {
            pos_x += csin(angle);
            pos_y -= ccos(angle);
        }
        if (CONTROLLER_IS_BTN_DOWN(controller)) {
            pos_x -= csin(angle);
            pos_y += ccos(angle);
        }
        if (CONTROLLER_IS_BTN_LEFT(controller)) {
            angle -= 16; // Turns counter-clockwise
        }
        if (CONTROLLER_IS_BTN_RIGHT(controller)) {
            angle += 16; // Turns clockwise
        }
        if (CONTROLLER_IS_BTN_TRIANGLE(controller)) {
            scale += 1;
        }
        if (CONTROLLER_IS_BTN_CROSS(controller)) {
            scale -= 1;
        }
    }
}

void update_player_position() {
    // Rotate the triangle coordinates based on the player's angle
    // as well as apply the position
    for (uint8_t i = 0; i < 3; i++) {
        v[i].vx = ((((player_tri[i].vx * ccos(angle)) - (player_tri[i].vy * csin(angle))) >> 12) + (pos_x >> 12)) * scale;
        v[i].vy = ((((player_tri[i].vy * ccos(angle)) + (player_tri[i].vx * csin(angle))) >> 12) + (pos_y >> 12)) * scale;
        FntPrint("vx%d=%d, vy%d=%d\n", i, v[i].vx, i, v[i].vy);
    }

    setXY3(&space_ship,
           v[0].vx, v[0].vy,
           v[1].vx, v[1].vy,
           v[2].vx, v[2].vy
    );
}







