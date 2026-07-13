#include "libgpu.h"
#include "../../lib/Graphics.h"

int main() {
    gfx_init();

    while(1) {
        gfx_clear_ot();
        FntPrint("Hello World!, curr buff = %d", gfx_current_frame());
        FntFlush(-1);

        gfx_display();
    }
}




