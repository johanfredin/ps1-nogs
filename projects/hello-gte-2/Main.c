#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Heap.h"

Controller *controller;

int main() {
    // Initialize system
    GPU_Init();
    GPU_SetBGColor(50, 50, 50);

    Heap_Init();
    Controller_Init();
    controller = CONTROLLER_READ_P1();

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
        GPU_ClearOT();
        FntPrint("Hello hello-gte-2\n");

        CONTROLLER_LOG_INPUT(controller); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here
        GPU_SortPolyFT4(&ship_poly, coords);


        GPU_Display();
    }
}







