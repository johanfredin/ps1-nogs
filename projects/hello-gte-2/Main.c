#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/Graphics.h"
#include "../../lib/Controller.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Heap.h"

Controller *ctrl;

int main() {
    // Initialize system
    gfx_init();
    gfx_set_bg_color(50, 50, 50);

    heap_init();
    ctrl_init();
    ctrl = ctrl_read(CTRL_PAD_1);

    CdData ship_data;
    POLY_FT4 ship_poly;
    TIM_IMAGE tim;

    cd_init();
    cd_data_init(&ship_data, "SHIP.TIM");
    // Load your resources here
    cd_acquire_data(&ship_data);
    asmg_load_poly_ft4(&ship_poly, &tim, &ship_data);


    uint8_t w = 87, h = 80;
    DVECTOR coords[4] = {
            100, 100,
            100 + w, 100,
            100, 100 + h,
            100 + w, 100 + h
    };

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        gfx_clear_ot();
        FntPrint("Hello hello-gte-2\n");

        CTRL_LOG_INPUT(ctrl); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here
        gfx_sort_poly_ft4(&ship_poly, coords);


        gfx_display();
    }
}







