//
// Created by johan on 2024-02-18.
//

#ifndef PS1_DEV_GRAPHICS_H
#define PS1_DEV_GRAPHICS_H

#include "libgpu.h"
#include "libetc.h"

#define GFX_SCREEN_W 320
#define GFX_SCREEN_H 240
#define GFX_OT_LEN 8
#define NULL 0


#define GFX_DR_TPAGE_INIT(dr_tpage, tim_image) setDrawTPage((dr_tpage), 0, 1,  getTPage((tim_image)->mode & 0x3, 0, (tim_image)->prect->x, (tim_image)->prect->y))

void gfx_init();
void gfx_clear_ot();
void gfx_display();

void gfx_sort_sprt(SPRT *sprt);
void gfx_sort_sprt_with_tpage(SPRT *sprt, DR_TPAGE *dr_tpage);
void gfx_sort_tile(TILE *tile);
void gfx_sort_dr_tpage(DR_TPAGE *dr_tpage);


#endif //PS1_DEV_GRAPHICS_H
