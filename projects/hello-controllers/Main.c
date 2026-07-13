#include <libgpu.h>

#include "../../lib/Controller.h"
#include "../../lib/GPU.h"

int main() {
    GPU_init();
    GPU_set_bg_color(0x10, 0x25, 0x55);
    ctrl_init();

    const Controller *p1 = ctrl_read(CTRL_PAD_1);

    while (1) {
        GPU_clear_ot();
        FntPrint("Hello Controllers!\n");
        CTRL_LOG_INPUT(p1);
        FntFlush(-1);
        GPU_display();
    }
}




