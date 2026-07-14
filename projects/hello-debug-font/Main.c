#include "libgpu.h"
#include "../../lib/GPU.h"

int main() {
    GPU_Init();

    while(1) {
        GPU_ClearOT();
        FntPrint("Hello World!, curr buff = %d", GPU_GetCurrentFrame());
        FntFlush(-1);

        GPU_Display();
    }
}




