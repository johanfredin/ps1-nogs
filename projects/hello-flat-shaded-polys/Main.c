#include "libgpu.h"
#include "../../lib/GPU.h"
#include "../../lib/PrimBuff.h"

void init_tile(TILE *tile, const short x, const short y, const u_short w, const u_short h, const u_char r, const u_char g, const u_char b) {
    setTile(tile);
    setXY0(tile, x, y);
    setWH(tile, w, h);
    setRGB0(tile, r, g, b);
}

int main() {
    GPU_Init();
    while (1) {
        // Clear ot
        GPU_ClearOT();
        PrimBuff_Clear(GPU_GetCurrentFrame());

        TILE *tile1 = PrimBuff_AcquireSlot(sizeof(TILE));
        init_tile(tile1, 60, 70, 32, 32, 110, 255, 0);

        TILE *tile2 = PrimBuff_AcquireSlot(sizeof(TILE));
        init_tile(tile2, 50, 50, 32, 32, 0, 255, 255);

        GPU_SortTile(tile1);
        GPU_SortTile(tile2);

        FntPrint("Hello Flat Shaded TILE %d", sizeof(TILE));
        FntFlush(-1);

        GPU_Display();
    }
}




