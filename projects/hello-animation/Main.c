#include "../../lib/CdReader.h"
#include "../../lib/Logger.h"
#include "../../lib/MemUtils.h"
#include "../../lib/Graphics.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Controller.h"
#include "../../lib/Animation.h"

Animation anim_idle, anim_walk_right;
Animation *current_anim;
SPRT cappy_sprite;

void check_pad(Controller *pad);

int main() {

    SPRT skybox_sprite;
    SPRT pillar_sprite;
    SPRT tree_sprite;
    DR_TPAGE dr_tpage_cappy;
    DR_TPAGE dr_tpage_skybox;
    DR_TPAGE dr_tpage_pillar;
    DR_TPAGE dr_tpage_tree;
    TIM_IMAGE tim_cappy;
    TIM_IMAGE tim_skybox;
    TIM_IMAGE tim_pillar;
    TIM_IMAGE tim_tree;


    // Initialize system
    gfx_init();

    ctrl_init();

    Controller *p1 = ctrl_read(CTRL_PAD_1);

    MEM_INIT_HEAP_3();
    CDR_INIT();
    // Acquire crash and cappy tims from cd
    CdrData *data_cappy = cdr_read_file("CAPPY.TIM");
    CdrData *data_skybox = cdr_read_file("SKYBOX.TIM");
    CdrData *data_pillar = cdr_read_file("PILLAR.TIM");
    CdrData *data_tree = cdr_read_file("TREE.TIM");
    CDR_CLOSE();

    // Acquire tim data
    asmg_load_sprt(&cappy_sprite, &tim_cappy, data_cappy);
    asmg_load_sprt(&skybox_sprite, &tim_skybox, data_skybox);
    asmg_load_sprt(&pillar_sprite, &tim_pillar, data_pillar);
    asmg_load_sprt(&tree_sprite, &tim_tree, data_tree);

    // Init dr tpages
    GFX_DR_TPAGE_INIT(&dr_tpage_cappy, &tim_cappy);
    GFX_DR_TPAGE_INIT(&dr_tpage_skybox, &tim_skybox);
    GFX_DR_TPAGE_INIT(&dr_tpage_pillar, &tim_pillar);
    GFX_DR_TPAGE_INIT(&dr_tpage_tree, &tim_tree);

    CDR_DATA_FREE(data_cappy);
    CDR_DATA_FREE(data_pillar);
    CDR_DATA_FREE(data_skybox);
    CDR_DATA_FREE(data_tree);

    setXY0(&cappy_sprite, 100, 128);
    setWH(&cappy_sprite, 64, 64);
    setXY0(&pillar_sprite, 64, 184);
    setXY0(&tree_sprite, 20, 0);

    // Create animation
    anim_init(&anim_idle, 4, 2, 15, 0);
    anim_init(&anim_walk_right, 4, 1, 5, 3);
    ctrl_init();

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        gfx_clear_ot();
        check_pad(p1);

        FntPrint("\cappy u=%d,v=%d, t=%d", cappy_sprite.u0, cappy_sprite.v0, current_anim->acc_ticks);
        setUV0(&cappy_sprite, ((current_anim->curr_col) * cappy_sprite.w), ((current_anim->curr_row) * cappy_sprite.h));
        gfx_sort_sprt_with_tpage(&cappy_sprite, &dr_tpage_cappy);
        gfx_sort_sprt_with_tpage(&pillar_sprite, &dr_tpage_pillar);
        gfx_sort_sprt_with_tpage(&tree_sprite, &dr_tpage_tree);
        gfx_sort_sprt_with_tpage(&skybox_sprite, &dr_tpage_skybox);

        gfx_display();
    }
}

void check_pad(Controller *pad) {
    // Get the id
    char *current_button = "";
    if (CTRL_IS_CONNECTED(pad)) {


        if (CTRL_NO_INPUT(pad)) {
            current_anim = anim_tick(&anim_idle);
        }

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
            current_anim = anim_tick(&anim_walk_right);
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





