#include "../../lib/CD.h"
#include "../../lib/Logger.h"
#include "../../lib/MemUtils.h"
#include "../../lib/Graphics.h"
#include "../../lib/AssetManager.h"

int main() {
    SPRT cappy_8bit;
    SPRT crash_16bit;
    SPRT raichu_8bit;
    SPRT psyduck_8bit;
    DR_TPAGE dr_tpage_8bit;
    DR_TPAGE dr_tpage_8bit_raichu;
    DR_TPAGE dr_tpage_16bit;
    TIM_IMAGE tim_crash;
    TIM_IMAGE tim_cappy;
    TIM_IMAGE tim_raichu;
    TIM_IMAGE tim_psyduck;

    // Initialize system
    gfx_init();

    MEM_INIT_HEAP_3();
    CDR_INIT();
    // Acquire crash and cappy tims from cd
    CdData *data_crash = cdr_read_file("CRASH.TIM");
    CdData *data_cappy = cdr_read_file("CAPPY.TIM");
    CdData *data_raichu = cdr_read_file("RAICHU.TIM");
    CdData *data_psyduck = cdr_read_file("PSYDUCK.TIM");
    CDR_CLOSE();

    // Acquire tim data
    asmg_load_sprt(&crash_16bit, &tim_crash, data_crash);
    asmg_load_sprt(&cappy_8bit, &tim_cappy, data_cappy);
    asmg_load_sprt(&raichu_8bit, &tim_raichu, data_raichu);
    asmg_load_sprt(&psyduck_8bit, &tim_psyduck, data_psyduck);

    // Init dr tpages
    GFX_DR_TPAGE_INIT(&dr_tpage_8bit, &tim_cappy);
    GFX_DR_TPAGE_INIT(&dr_tpage_16bit, &tim_crash);
    GFX_DR_TPAGE_INIT(&dr_tpage_8bit_raichu, &tim_raichu);

    CDR_DATA_FREE(data_crash);
    CDR_DATA_FREE(data_cappy);
    CDR_DATA_FREE(data_psyduck);
    CDR_DATA_FREE(data_raichu);

    // Cappy is a sprite sheet, we want one frame only
    setWH(&cappy_8bit, 64, 64);
    setXY0(&cappy_8bit, 240, 60);
    setXY0(&raichu_8bit, 300, 20);
    setXY0(&psyduck_8bit, 300, 40);
    while (1) {
        // Clear ot
        gfx_clear_ot();

        FntPrint("                  Hello Textured sprites\n");

        gfx_sort_sprt(&cappy_8bit);
        gfx_sort_dr_tpage(&dr_tpage_8bit);

        // Psyduck and raichu are stored in the same texture page so we can use the same DR_TPAGE for them
        gfx_sort_sprt(&raichu_8bit);
        gfx_sort_sprt(&psyduck_8bit);
        gfx_sort_dr_tpage(&dr_tpage_8bit_raichu);

        gfx_sort_sprt(&crash_16bit);
        gfx_sort_dr_tpage(&dr_tpage_16bit);


        gfx_display();
    }
}





