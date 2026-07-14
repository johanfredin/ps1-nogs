#include <libgpu.h>

#include "../../lib/Controller.h"
#include "../../lib/GPU.h"

int main() {
    GPU_Init();
    GPU_SetBGColor(0x10, 0x25, 0x55);
    Controller_Init();

    const Controller *p1 = Controller_Read(CONTROLLER_PAD_1);

    while (1) {
        GPU_ClearOT();
        FntPrint("Hello Controllers!\n");
        CONTROLLER_LOG_INPUT(p1);
        FntFlush(-1);
        GPU_Display();
    }
}




