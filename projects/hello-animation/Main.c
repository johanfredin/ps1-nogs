#include "../../lib/CD.h"
#include "../../lib/Heap.h"
#include "../../lib/GPU.h"
#include "../../lib/AssetManager.h"
#include "../../lib/Controller.h"
#include "../../lib/Animation.h"

static Animation anim_idle, anim_walk_right;
static Animation *current_anim;
static SPRT cappy_sprite;

static void check_pad(const Controller *pad);

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
    GPU_Init();

    Controller_Init();

    const Controller *p1 = Controller_Read(CONTROLLER_PAD_1);

    Heap_Init();
    CD_Init();
    // Acquire crash and cappy tims from cd
    CdData *data_cappy = CD_DataMalloc("CAPPY.TIM");
    CdData *data_skybox = CD_DataMalloc("SKYBOX.TIM");
    CdData *data_pillar = CD_DataMalloc("PILLAR.TIM");
    CdData *data_tree = CD_DataMalloc("TREE.TIM");

    // Acquire tim data
    AssetManager_LoadSprite(&cappy_sprite, &tim_cappy, data_cappy);
    AssetManager_LoadSprite(&skybox_sprite, &tim_skybox, data_skybox);
    AssetManager_LoadSprite(&pillar_sprite, &tim_pillar, data_pillar);
    AssetManager_LoadSprite(&tree_sprite, &tim_tree, data_tree);

    // Init dr tpages
    GPU_DR_TPAGE_INIT(&dr_tpage_cappy, &tim_cappy);
    GPU_DR_TPAGE_INIT(&dr_tpage_skybox, &tim_skybox);
    GPU_DR_TPAGE_INIT(&dr_tpage_pillar, &tim_pillar);
    GPU_DR_TPAGE_INIT(&dr_tpage_tree, &tim_tree);

    CD_Free(data_cappy);
    CD_Free(data_pillar);
    CD_Free(data_skybox);
    CD_Free(data_tree);

    setXY0(&cappy_sprite, 100, 128);
    setWH(&cappy_sprite, 64, 64);
    setXY0(&pillar_sprite, 64, 184);
    setXY0(&tree_sprite, 20, 0);

    // Create animation
    Animation_Init(&anim_idle, 4, 2, 15, 0);
    Animation_Init(&anim_walk_right, 4, 1, 5, 3);

    // Cappy is a sprite sheet, we want one frame only
    while (1) {
        // Clear ot
        GPU_ClearOT();
        check_pad(p1);

        FntPrint("\n cappy u=%d,v=%d, t=%d", cappy_sprite.u0, cappy_sprite.v0, current_anim->acc_ticks);
        setUV0(&cappy_sprite, ((current_anim->curr_col) * cappy_sprite.w), ((current_anim->curr_row) * cappy_sprite.h));
        GPU_SortSpriteWithTPage(&cappy_sprite, &dr_tpage_cappy);
        GPU_SortSpriteWithTPage(&pillar_sprite, &dr_tpage_pillar);
        GPU_SortSpriteWithTPage(&tree_sprite, &dr_tpage_tree);
        GPU_SortSpriteWithTPage(&skybox_sprite, &dr_tpage_skybox);

        GPU_Display();
    }
}

static void check_pad(const Controller *pad) {
    // Get the id
    if (CONTROLLER_IS_CONNECTED(pad)) {
        if (CONTROLLER_NO_INPUT(pad)) {
            current_anim = Animation_Tick(&anim_idle);
        }
        if (CONTROLLER_IS_BTN_RIGHT(pad)) {
            current_anim = Animation_Tick(&anim_walk_right);
        }
    }

}





