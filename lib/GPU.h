//
// Created by johan on 2024-02-18.
//

#ifndef PS1_DEV_GRAPHICS_H
#define PS1_DEV_GRAPHICS_H

#include <stdint.h>

#include "libgpu.h"
#include "sys/types.h"

#define GPU_SCREEN_W 320
#define GPU_SCREEN_H 240

//TODO should be dynamic
#define GPU_OT_LEN 2048

#define GPU_DR_TPAGE_INIT(dr_tpage, tim_image) \
    setDrawTPage((dr_tpage), 0, 1,  getTPage((tim_image)->mode & 0x3, 0, (tim_image)->prect->x, (tim_image)->prect->y))

void GPU_Init(void);
void GPU_SetBGColor(uint8_t r, uint8_t g, uint8_t b);
void GPU_ClearOT(void);
void GPU_Display(void);

void GPU_SortSprite(SPRT *sprite);
void GPU_InitPolyF3(POLY_F3 *poly, const SVECTOR *v, uint8_t r, uint8_t g, uint8_t b);
void GPU_SortSpriteWithTPage(SPRT *sprt, DR_TPAGE *dr_tpage);
void GPU_SortTile(TILE *tile);
void GPU_SortPolyF3(POLY_F3 *poly);
void GPU_SortPolyF4(POLY_F4 *poly, const DVECTOR *v);
void GPU_SortPolyFT4(POLY_FT4 *poly, const DVECTOR *v);
void GPU_SortDRTPage(DR_TPAGE *dr_tpage);
uint8_t GPU_GetCurrentFrame(void);


#endif //PS1_DEV_GRAPHICS_H
