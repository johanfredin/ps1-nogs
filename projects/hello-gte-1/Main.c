#include <libgpu.h>
#include <libgte.h>
#include "../../lib/CD.h"
#include "../../lib/Logger.h"
#include "../../lib/MemUtils.h"
#include "../../lib/Graphics.h"
#include "../../lib/Controller.h"

Controller *ctrl;
POLY_F3 space_ship;
SVECTOR v[3];

// For the player triangle
SVECTOR player_tri[3] = {
        {0,   -20, ONE  * 2},
        {10,  20, ONE * 2},
        {-10, 20, ONE * 2},
};

int32_t pos_x = ONE * (GFX_SCREEN_W >> 1);
int32_t pos_y = ONE * (GFX_SCREEN_H >> 1);

int angle = 0;
int scale = 1;

void check_pad();
void update_player_position();

int main() {
    // Initialize system
    gfx_init();
    ctrl_init();

    gfx_init_poly_f3(&space_ship, player_tri, 255, 255, 0);

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        gfx_clear_ot();

        // Print player coordinates
        FntPrint("POS_X=%d (%d.%d)\n", pos_x, (pos_x>>12), (pos_x&0xfff) );
        FntPrint("POS_Y=%d (%d.%d)\n", pos_y, (pos_y>>12), (pos_y&0xfff) );
        FntPrint("ANGLE=%d, SCALE=%d\n", angle, scale);

        check_pad();
        update_player_position();

        // Add your update and draw function calls here
        gfx_sort_poly_f3(&space_ship);

        gfx_display();
    }
}

void check_pad() {
    ctrl = ctrl_read(CTRL_PAD_1);
    if (CTRL_IS_CONNECTED(ctrl)) {
        if (CTRL_IS_BTN_UP(ctrl)) {
            pos_x += csin(angle);
            pos_y -= ccos(angle);
        }
        if (CTRL_IS_BTN_DOWN(ctrl)) {
            pos_x -= csin(angle);
            pos_y += ccos(angle);
        }
        if (CTRL_IS_BTN_LEFT(ctrl)) {
            angle -= 16; // Turns counter-clockwise
        }
        if (CTRL_IS_BTN_RIGHT(ctrl)) {
            angle += 16; // Turns clockwise
        }
        if (CTRL_IS_BTN_TRIANGLE(ctrl)) {
            scale += 1;
        }
        if (CTRL_IS_BTN_CROSS(ctrl)) {
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







