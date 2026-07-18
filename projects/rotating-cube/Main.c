#include "libgpu.h"
#include "../../lib/GPU.h"
#include "../../lib/GTE.h"
#include "../../lib/PrimBuff.h"

#define NUM_VERTICES 8
#define NUM_FACES 6

SVECTOR vertices[NUM_VERTICES] = {
    { -128, -128, -128 },
    {  128, -128, -128 },
    {  128, -128,  128 },
    { -128, -128,  128 },
    { -128,  128, -128 },
    {  128,  128, -128 },
    {  128,  128,  128 },
    { -128,  128,  128 },
  };

short faces[] = {
    3, 2, 0, 1,  // top quad
    0, 1, 4, 5,  // front quad
    4, 5, 7, 6,  // bottom quad
    1, 2, 5, 6,  // right quad
    2, 3, 6, 7,  // back quad
    3, 0, 7, 4,  // left quad
  };

static SVECTOR rotation = {0, 0, 0};
static VECTOR translation = {0, 0, 900};
static VECTOR scale = {ONE, ONE, ONE};

static MATRIX world_matrix = {0};

int main() {
    // Initialize system
    GPU_Init();
    GTE_Init();

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        GTE_SetRTS(&world_matrix, &rotation, &translation, &scale);

        // Clear ot
        GPU_ClearOT();
        PrimBuff_Clear(GPU_GetCurrentFrame());
        FntPrint("rotating-cube\n");
        long otz, p, flg;

        for (size_t i = 0; i < NUM_FACES * 4; i += 4) {
            POLY_G4 *poly = PrimBuff_AcquireSlot(sizeof(POLY_G4));
            setPolyG4(poly);
            setRGB0(poly, 255, 0, 255);
            setRGB1(poly, 255, 255, 0);
            setRGB2(poly, 0, 255, 255);
            setRGB3(poly, 0, 255, 0);

            const long n_clip = RotAverageNclip4(
                &vertices[faces[i + 0]],
                &vertices[faces[i + 1]],
                &vertices[faces[i + 2]],
                &vertices[faces[i + 3]],
                (long *)&poly->x0,
                (long *)&poly->x1,
                (long *)&poly->x2,
                (long *)&poly->x3,
                &p, &otz, &flg
            );
            if (n_clip <= 0) {
                continue;
            }
            if ((otz > 0) && (otz < GPU_OT_LEN)) {
                GPU_SortPrim(poly, otz);
            }
        }

        rotation.vx += 6;
        rotation.vy += 8;
        rotation.vz += 12;
        GPU_Display();
    }
}







