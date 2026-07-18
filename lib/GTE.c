#include "GTE.h"
#include <libgte.h>
#include <stdbool.h>

#include "Log.h"
#include "stdio.h"

static VECTOR SCALE_DEFAULT = {ONE, ONE, ONE};

void GTE_Init(void) {
    InitGeom();
    SetGeomOffset(GTE_CENTER_X, GTE_CENTER_Y);
    SetGeomScreen(GTE_SCREEN_Z);
    LOG_INFO("GTE initialized, center-x/y={%d,%d}, z=%d", GTE_CENTER_X, GTE_CENTER_Y, GTE_SCREEN_Z);
}

void GTE_SetRT(MATRIX *world_matrix, SVECTOR *rot, VECTOR *trans) {
    GTE_SetRTS(world_matrix, rot, trans, &SCALE_DEFAULT);
}

void GTE_SetRTS(MATRIX *world_matrix, SVECTOR *rot, VECTOR *trans, VECTOR *scale) {
    RotMatrix(rot, world_matrix);
    TransMatrix(world_matrix, trans);
    ScaleMatrix(world_matrix, scale);

    SetRotMatrix(world_matrix);
    SetTransMatrix(world_matrix);
}

bool GTE_ProjectCube(SVECTOR *vertices, const short *faces, const size_t *i, long *x0, long *x1, long *x2, long *x3, long *otz) {
    long p, flg; //Unused
    const long n_clip = RotAverageNclip4(
        &vertices[faces[*i + 0]],
        &vertices[faces[*i + 1]],
        &vertices[faces[*i + 2]],
        &vertices[faces[*i + 3]],
        x0,
        x1,
        x2,
        x3,
        &p, otz, &flg
    );
    return n_clip > 0;
}
