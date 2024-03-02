#include "libgpu.h"
#include "../../lib/CdReader.h"
#include "../../lib/Logger.h"
#include "../../lib/MemUtils.h"
#include "../../lib/Graphics.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Controller.h"

void check_pad(Controller *pad);

int main() {
    SPRT raichu_8bit;
    DR_TPAGE dr_tpage_8bit_raichu;
    TIM_IMAGE tim_raichu;

    // Initialize system
    gfx_init();

    ctrl_init();

    Controller *p1 = ctrl_read(CTRL_PAD_1);

    MEM_INIT_HEAP_3();
    CDR_INIT();
    // Acquire crash and cappy tims from cd
    CdrData *data_raichu = cdr_read_file("RAICHU.TIM");
    CDR_CLOSE();

    // Acquire tim data
    asmg_load_sprt(&raichu_8bit, &tim_raichu, data_raichu);

    // Init dr tpages
    GFX_DR_TPAGE_INIT(&dr_tpage_8bit_raichu, &tim_raichu);

    CDR_DATA_FREE(data_raichu);

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        gfx_clear_ot();

        FntPrint("hello-rotating-polys\n");

        check_pad(p1);
        gfx_sort_sprt(&raichu_8bit);
        gfx_sort_dr_tpage(&dr_tpage_8bit_raichu);


        gfx_display();
    }
}


void check_pad(Controller *pad) {
    // Get the id
    char *current_button = "";
    if (CTRL_IS_CONNECTED(pad)) {
        if (CTRL_IS_BTN_UP(pad)) {
            current_button = "UP";
        }
        if (CTRL_IS_BTN_DOWN(pad)) {
            current_button = "DOWN";
        }
        if (CTRL_IS_BTN_LEFT(pad)) {
            current_button = "LEFT";
        }
        if (CTRL_IS_BTN_RIGHT(pad)) {
            current_button = "RIGHT";
        }
        if (CTRL_IS_BTN_CROSS(pad)) {
            current_button = "X";
        }
        if (CTRL_IS_BTN_SQUARE(pad)) {
            current_button = "[]";
        }
        if (CTRL_IS_BTN_CIRCLE(pad)) {
            current_button = "()";
        }
        if (CTRL_IS_BTN_TRIANGLE(pad)) {
            current_button = "/\\";
        }
        if (CTRL_IS_BTN_START(pad)) {
            current_button = "START";
        }
        if (CTRL_IS_BTN_SELECT(pad)) {
            current_button = "SELECT";
        }
        if (CTRL_IS_BTN_R1(pad)) {
            current_button = "R1";
        }
        if (CTRL_IS_BTN_R2(pad)) {
            current_button = "R2";
        }
        if (CTRL_IS_BTN_L1(pad)) {
            current_button = "L1";
        }
        if (CTRL_IS_BTN_L2(pad)) {
            current_button = "L2";
        }
        FntPrint("Controller connected\nButton pressed=%s", current_button);
    }

}





