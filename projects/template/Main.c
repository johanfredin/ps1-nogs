#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"
#include "../../lib/Heap.h"

static Controller *controller;

int main() {
    // Initialize system
    GPU_Init();

    Controller_Init();
    controller = Controller_Read(CONTROLLER_PAD_1);

    Heap_Init();
    CD_Init();
    // Load your resources here


    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        GPU_ClearOT();
        FntPrint("$template\n");

        CONTROLLER_LOG_INPUT(controller); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here

        GPU_Display();
    }
}







