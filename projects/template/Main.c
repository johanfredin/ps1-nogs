#include "libgpu.h"
#include "../../lib/CD.h"
#include "../../lib/Logger.h"
#include "../../lib/MemUtils.h"
#include "../../lib/Graphics.h"
#include "../../lib/Controller.h"
#include "../../lib/AssetManager.h"

Controller *ctrl;

int main() {
    // Initialize system
    gfx_init();

    ctrl_init();
    ctrl = ctrl_read(CTRL_PAD_1);

    MEM_INIT_HEAP_3();
    CDR_INIT();
    // Load your resources here

    CDR_CLOSE();

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







