#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Heap.h"

Controller *ctrl;

int main() {
    // Initialize system
    GPU_init();
    GPU_set_bg_color(50, 50, 50);

    heap_init();
    ctrl_init();
    ctrl = ctrl_read(CTRL_PAD_1);

    CdData ship_data = {};
    POLY_FT4 ship_poly;
    TIM_IMAGE tim;

    CD_Init();
    ship_data.name = "SHIP.TIM";
    // Load your resources here
    CD_AcquireData(&ship_data);
    AssetManager_LoadPolyFT4(&ship_poly, &tim, &ship_data);


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
        GPU_clear_ot();
        FntPrint("Hello hello-gte-2\n");

        CTRL_LOG_INPUT(ctrl); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here
        GPU_sort_poly_ft4(&ship_poly, coords);


        GPU_display();
    }
}







