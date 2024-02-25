#include "libgpu.h"
#include "libetc.h"

#define SCREEN_W 320
#define SCREEN_H 240
#define NUM_BUFFERS 2
#define OT_LEN 8
#define PRIM_BUFF_32K 32768
#define NULL 0

DISPENV disp_env[NUM_BUFFERS];
DRAWENV draw_env[NUM_BUFFERS];

// Ordering table
u_long ot[NUM_BUFFERS][OT_LEN];

// Current buffer
u_char current_buffer;

void init() {
    // Reset gpu and enable interrupts
    ResetGraph(0);

    // Set the video mode (default is NTSC so not required here)
    SetVideoMode(MODE_NTSC);

    // Configure the DISPENVs for NTSC mode
    SetDefDispEnv(&disp_env[0], 0, 0, SCREEN_W, SCREEN_H);
    SetDefDispEnv(&disp_env[1], 0, SCREEN_H, SCREEN_W, SCREEN_H);

    // Configure the pair of DRAWENVs for the DISPENVs
    SetDefDrawEnv(&draw_env[0], 0, SCREEN_H, SCREEN_W, SCREEN_H);
    SetDefDrawEnv(&draw_env[1], 0, 0, SCREEN_W, SCREEN_H);

    // Specifies the clear color of the DRAWENV
    setRGB0(&draw_env[0], 63, 0, 127);
    setRGB0(&draw_env[1], 63, 0, 127);

    // Enable background clear
    draw_env[0].isbg = 1;
    draw_env[1].isbg = 1;

    // Apply environments
    PutDispEnv(&disp_env[0]);
    PutDrawEnv(&draw_env[0]);

    current_buffer = 0;

    FntLoad(960, 0);
    FntOpen(20, 20, SCREEN_W, 50, 0, 256);

}

void init_tile(TILE *tile, short x, short y, u_short w, u_short h, u_char r, u_char g, u_char  b) {
    setTile(tile);
    setXY0(tile, x, y);
    setWH(tile, w, h);
    setRGB0(tile, r, g, b);
}

void display() {
    // Wait for GPU to finish drawing and V-Blank
    DrawSync(0);
    VSync(0);

    // Apply environments
    PutDispEnv(&disp_env[current_buffer]);
    PutDrawEnv(&draw_env[current_buffer]);

    // Enable display
    SetDispMask(1);

    // Draw the ordering table
    DrawOTag(&ot[current_buffer][OT_LEN - 1]);

    // Flip current buffer
    current_buffer = !current_buffer;
}

int main() {
    init();
    TILE tile1, tile2;
    init_tile(&tile1, 60, 70, 32, 32, 110, 255, 0);
    init_tile(&tile2, 50, 50, 32, 32, 0, 255, 255);

    while (1) {
        // Clear ot
        ClearOTagR(ot[current_buffer], OT_LEN);
        addPrim(ot[current_buffer], &tile1);
        addPrim(ot[current_buffer], &tile2);

        FntPrint("Hello Flat Shaded TILE %d", sizeof(TILE));
        FntFlush(-1);

        display();
    }
}




