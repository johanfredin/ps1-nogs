#include "libgpu.h"
#include "../../lib/GPU.h"

int main() {
    GPU_init();

    while(1) {
        GPU_clear_ot();
        FntPrint("Hello World!, curr buff = %d", GPU_current_frame());
        FntFlush(-1);

        GPU_display();
    }
}




