//
// Created by johan on 2024-02-18.
//

#include "Graphics.h"

DISPENV disp_env[2];
DRAWENV draw_env[2];

// Ordering table
u_long ot[2][GFX_OT_LEN];

// Current buffer
u_short current_buffer;

void gfx_init() {
    // Reset gpu and enable interrupts
    ResetGraph(0);

    // Set the video mode (default is NTSC so not required here)
    SetVideoMode(MODE_NTSC);

    // Configure the DISPENVs for NTSC mode
    SetDefDispEnv(&disp_env[0], 0, 0, GFX_SCREEN_W, GFX_SCREEN_H);
    SetDefDispEnv(&disp_env[1], 0, GFX_SCREEN_H, GFX_SCREEN_W, GFX_SCREEN_H);

    // Configure the pair of DRAWENVs for the DISPENVs
    SetDefDrawEnv(&draw_env[0], 0, GFX_SCREEN_H, GFX_SCREEN_W, GFX_SCREEN_H);
    SetDefDrawEnv(&draw_env[1], 0, 0, GFX_SCREEN_W, GFX_SCREEN_H);

    // Specifies the clear color of the DRAWENV
    gfx_set_bg_color(0, 0, 0);

    // Enable background clear
    draw_env[0].isbg = 1;
    draw_env[1].isbg = 1;

    // Apply environments
    PutDispEnv(&disp_env[0]);
    PutDrawEnv(&draw_env[0]);

    current_buffer = 0;

    FntLoad(960, 0);
    FntOpen(20, 10, GFX_SCREEN_W, 50, 0, 256);

    // Enable display
    SetDispMask(1);
}

void gfx_set_bg_color(uint8_t r, uint8_t g, uint8_t b) {
    setRGB0(&draw_env[0], r, g, b);
    setRGB0(&draw_env[1], r, g, b);
}

void gfx_clear_ot() {
    ClearOTagR(ot[current_buffer], GFX_OT_LEN);
}

void gfx_display() {
    FntFlush(-1);

    // Wait for GPU to finish drawing and V-Blank
    DrawSync(0);
    VSync(0);

    // Apply environments
    PutDispEnv(&disp_env[current_buffer]);
    PutDrawEnv(&draw_env[current_buffer]);

    // Draw the ordering table
    DrawOTag(&ot[current_buffer][GFX_OT_LEN - 1]);

    // Flip current buffer
    current_buffer = !current_buffer;
}

void gfx_init_poly_f3(POLY_F3 *poly, SVECTOR *v, uint8_t r, uint8_t g, uint8_t b) {
    setPolyF3(poly);
    setRGB0(poly, r, g, b);
    setXY3(
            poly,
            v[0].vx, v[0].vy,
            v[1].vx, v[1].vy,
            v[2].vx, v[2].vy
    );
}

void gfx_sort_sprt(SPRT *sprt) {
    addPrim(&ot[current_buffer], sprt);
}

void gfx_sort_sprt_with_tpage(SPRT *sprt, DR_TPAGE *dr_tpage) {
    addPrim(&ot[current_buffer], sprt);
    addPrim(&ot[current_buffer], dr_tpage);
}

void gfx_sort_tile(TILE *tile) {
    addPrim(&ot[current_buffer], tile);
}

void gfx_sort_poly_f3(POLY_F3 *poly) {
    addPrim(&ot[current_buffer], poly);
}

void gfx_sort_poly_ft4(POLY_FT4 *poly, DVECTOR *v) {
    setXY4(
            poly,
            v[0].vx, v[0].vy,
            v[1].vx, v[1].vy,
            v[2].vx, v[2].vy,
            v[3].vx, v[3].vy
    );
    addPrim(&ot[current_buffer], poly);
}

void gfx_sort_poly_f4(POLY_F4 *poly, DVECTOR *v) {
    setXY4(
            poly,
            v[0].vx, v[0].vy,
            v[1].vx, v[1].vy,
            v[2].vx, v[2].vy,
            v[3].vx, v[3].vy
    );
    addPrim(&ot[current_buffer], poly);
}

void gfx_sort_dr_tpage(DR_TPAGE *dr_tpage) {
    addPrim(&ot[current_buffer], dr_tpage);
}

