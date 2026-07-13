#include "libgpu.h"
#include "../../lib/Graphics.h"

void init_tile(TILE *tile, short x, short y, u_short w, u_short h, u_char r, u_char g, u_char  b) {
    setTile(tile);
    setXY0(tile, x, y);
    setWH(tile, w, h);
    setRGB0(tile, r, g, b);
}

int main() {
    gfx_init();
    TILE tile1, tile2;
    init_tile(&tile1, 60, 70, 32, 32, 110, 255, 0);
    init_tile(&tile2, 50, 50, 32, 32, 0, 255, 255);

    while (1) {
        // Clear ot
        gfx_clear_ot();
        gfx_sort_tile(&tile1);
        gfx_sort_tile(&tile2);

        FntPrint("Hello Flat Shaded TILE %d", sizeof(TILE));
        FntFlush(-1);

        gfx_display();
    }
}




