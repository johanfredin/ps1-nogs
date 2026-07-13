#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/GPU.h"
#include "../../lib/Controller.h"
#include "../../lib/Heap.h"

Controller *ctrl;

int main() {
    // Initialize system
    GPU_init();

    ctrl_init();
    ctrl = ctrl_read(CTRL_PAD_1);

    heap_init();
    cd_init();
    // Load your resources here


    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        gfx_clear_ot();
        FntPrint("$template\n");

        CTRL_LOG_INPUT(ctrl); // Just for debugging purposes, remove later on!

        // Add your update and draw function calls here



        gfx_display();
    }
}







