//
// Created by johan on 2024-02-18.
//

#include "GPU.h"
#include <libetc.h>
#include <stdint.h>

static DISPENV disp_env[2];
static DRAWENV draw_env[2];

// Ordering table
static unsigned long ot[2][GPU_OT_LEN];

// Current buffer
static uint8_t current_buffer;

void GPU_Init(void) {
    // Reset gpu and enable interrupts
    ResetGraph(MODE_NTSC);

    // Set the video mode (default is NTSC so not required here)
    SetVideoMode(0);

    // Configure the DISPENVs for NTSC mode
    SetDefDispEnv(&disp_env[0], 0, 0, GPU_SCREEN_W, GPU_SCREEN_H);
    SetDefDispEnv(&disp_env[1], 0, GPU_SCREEN_H, GPU_SCREEN_W, GPU_SCREEN_H);

    // Configure the pair of DRAWENVs for the DISPENVs
    SetDefDrawEnv(&draw_env[0], 0, GPU_SCREEN_H, GPU_SCREEN_W, GPU_SCREEN_H);
    SetDefDrawEnv(&draw_env[1], 0, 0, GPU_SCREEN_W, GPU_SCREEN_H);

    // Specifies the clear color of the DRAWENV
    GPU_SetBGColor(0, 0, 0);

    // Enable background clear
    draw_env[0].isbg = 1;
    draw_env[1].isbg = 1;

    // Apply environments
    PutDispEnv(&disp_env[0]);
    PutDrawEnv(&draw_env[0]);

    current_buffer = 0;

    FntLoad(960, 0);
    FntOpen(20, 10, GPU_SCREEN_W, 50, 0, 256);

    // Enable display
    SetDispMask(1);
}

void GPU_SetBGColor(const u_char r, const u_char g, const u_char b) {
    setRGB0(&draw_env[0], r, g, b);
    setRGB0(&draw_env[1], r, g, b);
}

uint8_t GPU_GetCurrentFrame(void) {
    return current_buffer;
}

void GPU_ClearOT() {
    ClearOTagR(ot[current_buffer], GPU_OT_LEN);
}

void GPU_Display() {
    FntFlush(-1);

    // Wait for GPU to finish drawing and V-Blank
    DrawSync(0);
    VSync(0);

    // Apply environments
    PutDispEnv(&disp_env[current_buffer]);
    PutDrawEnv(&draw_env[current_buffer]);

    // Draw the ordering table
    DrawOTag(&ot[current_buffer][GPU_OT_LEN - 1]);

    // Flip current buffer
    current_buffer = !current_buffer;
}

void GPU_InsertPrim(void *prim) {
    addPrim(&ot[current_buffer], prim);
}

void GPU_SortPrim(void *prim, const long otz) {
    addPrim(&ot[current_buffer][otz], prim);
}


