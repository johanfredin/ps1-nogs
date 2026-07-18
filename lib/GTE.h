//
// Created by johan on 2026-07-15.
//

#ifndef PS1_DEV_GTE_H
#define PS1_DEV_GTE_H

#include <stdbool.h>

#include "GPU.h"

#define GTE_CENTER_X (GPU_SCREEN_W >> 1)
#define GTE_CENTER_Y (GPU_SCREEN_H >> 1)
#define GTE_SCREEN_Z 320

typedef struct GTE_ProjectedPrim {
    long vertices[4];
} GTE_ProjectedPrim;

void GTE_Init(void);
void GTE_SetRT(MATRIX *world_matrix, SVECTOR *rot, VECTOR *trans);
void GTE_SetRTS(MATRIX *world_matrix, SVECTOR *rot, VECTOR *trans, VECTOR *scale);
bool GTE_ProjectCube(SVECTOR *vertices, const short *faces, const size_t *i, long *x0, long *x1, long *x2, long *x3, long *otz);
#endif //PS1_DEV_GTE_H
