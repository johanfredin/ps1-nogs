//
// Created by johan on 2024-02-18.
//

#ifndef PS1_DEV_GRAPHICS_H
#define PS1_DEV_GRAPHICS_H

#include <stdint.h>

#include "libgpu.h"
#include "sys/types.h"

#define GFX_SCREEN_W 320
#define GFX_SCREEN_H 240

//TODO should be dynamic
#define GFX_OT_LEN 8

#define GPU_DR_TPAGE_INIT(dr_tpage, tim_image) \
    setDrawTPage((dr_tpage), 0, 1,  getTPage((tim_image)->mode & 0x3, 0, (tim_image)->prect->x, (tim_image)->prect->y))

void GPU_init();
void GPU_set_bg_color(uint8_t r, uint8_t g, uint8_t b);
void GPU_clear_ot();
void GPU_display();

void GPU_sort_sprt(SPRT *sprt);
void GPU_init_poly_f3(POLY_F3 *poly, SVECTOR *v, uint8_t r, uint8_t g, uint8_t b);
void GPU_sort_sprt_with_tpage(SPRT *sprt, DR_TPAGE *dr_tpage);
void GPU_sort_tile(TILE *tile);
void GPU_sort_poly_f3(POLY_F3 *poly);
void GPU_sort_poly_f4(POLY_F4 *poly, DVECTOR *v);
void GPU_sort_poly_ft4(POLY_FT4 *poly, DVECTOR *v);
void GPU_sort_dr_tpage(DR_TPAGE *dr_tpage);
uint8_t GPU_current_frame();


#endif //PS1_DEV_GRAPHICS_H
