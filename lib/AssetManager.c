#include "stdlib.h"
#include "libspu.h"

#include "AssetManager.h"
#include "Logger.h"
#include "Graphics.h"

/*
 * Get the vram tim_data size using bitplane info (because vram position is in 16bits mode only)
 * From the great tutorials from orion!
 */
#define ImageToVRamSize(size, mode) ((size) / (1 << (2 - ((mode) & 3))))
#define VRamToImageSize(size, mode) ((size) * (1 << (2 - ((mode) & 3))))

SpuCommonAttr spu_common_attr;
SpuVoiceAttr spu_voice_attr;
long vag_spu_addr;
char rec[SPU_MALLOC_RECSIZ * (ASMG_SOUND_MALLOC_MAX + 1)];

void asmg_load_tim_data(TIM_IMAGE *tim_data, CdrData *cdr_data) {
    // Read TIM information
    OpenTIM(cdr_data->file);
    ReadTIM(tim_data);

    // Upload pixel data to framebuffer
    LoadImage(tim_data->prect, tim_data->paddr);
    DrawSync(0);
    logr_log(INFO, "Main.c", "load_tim_data",
             "Texture loaded from %s {x, y, w, h}=%d, %d, %d, %d", cdr_data->name, tim_data->prect->x, tim_data->prect->y,
             tim_data->prect->w, tim_data->prect->h);

    // Upload CLUT to framebuffer if present
    if (tim_data->mode & 0x8) {
        LoadImage(tim_data->crect, tim_data->caddr);
        DrawSync(0);
        logr_log(INFO, "Main.c", "load_tim_data",
                 "Clut added for %s {x, y}=%d, %d", cdr_data->name, tim_data->crect->x, tim_data->crect->y);
    }
}

void asmg_load_sprt(SPRT *sprite, TIM_IMAGE *tim, CdrData *cdr_data) {
    asmg_load_tim_data(tim, cdr_data);

    setSprt(sprite);

    // Set sprite size
    short w = sprite->w = tim->prect->w << (2 - tim->mode & 0x3);
    short h = sprite->h = tim->prect->h;
    setWH(sprite, w, h);

    // Get CLUT values (if sprite not 16 bit)
    if (tim->mode & 0x8) {
        sprite->clut = getClut(tim->crect->x, tim->crect->y);
    }

    // Set UV offset
    u_short sprite_u = ((tim->prect->x & 0x3f) << (2 - tim->mode & 0x3));
    u_short sprite_v = (tim->prect->y & 0xff);
    setUV0(sprite, sprite_u, sprite_v);
    setRGB0(sprite, 128, 128, 128);

    logr_log(INFO, "Main.c", "set_sprite",
             "Sprite initialized {x, y, w, h, u, v}=%d, %d, %d, %d, %d, %d",
             sprite->x0, sprite->y0, sprite->w, sprite->h, sprite->u0, sprite->v0
    );
}

void asmg_audio_init() {
    SpuInit();
    SpuInitMalloc(ASMG_SOUND_MALLOC_MAX, rec);
    spu_common_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    spu_common_attr.mvol.left = 0x3fff;     // Master left vol
    spu_common_attr.mvol.right = 0x3fff;    // Master right vol
    spu_voice_attr.mask = 0xFFFFFF;
    SpuSetCommonAttr(&spu_common_attr);
    SpuSetVoiceAttr(&spu_voice_attr);
    logr_log(INFO, "AssetManager.c", "asmg_audio_init", "SPU initialized");
}

void asmg_transfer_vag_to_spu(CdrData *cdr_data, u_long voice_channel) {
    SpuSetTransferMode(SpuTransByDMA);                                   // set transfer mode to DMA
    vag_spu_addr = SpuMalloc((long)(cdr_data->sectors) * CDR_SECTOR);     // allocate SPU memory for sound
    if(vag_spu_addr == -1) {
        logr_log(ERROR, "AssetManager.c", "asmg_transfer_vag_to_spu", "Could not allocate audio file %s, shutting down", cdr_data->name);
        exit(1);
    }

    SpuSetTransferStartAddr(vag_spu_addr);                           // set transfer starting address to malloced area
    u_char *vag_file = (u_char *) cdr_data->file;
    ASMG_AUDIO_SKIP_VAG_HEADER(vag_file);
    SpuWrite(vag_file, cdr_data->sectors * CDR_SECTOR);         // perform actual transfer
    SpuIsTransferCompleted(SPU_TRANSFER_WAIT);                       // wait for dma to complete
    spu_voice_attr.mask = (
            SPU_VOICE_VOLL |
            SPU_VOICE_VOLR |
            SPU_VOICE_PITCH |
            SPU_VOICE_WDSA |
            SPU_VOICE_ADSR_AMODE |
            SPU_VOICE_ADSR_SMODE |
            SPU_VOICE_ADSR_RMODE |
            SPU_VOICE_ADSR_AR |
            SPU_VOICE_ADSR_DR |
            SPU_VOICE_ADSR_SR |
            SPU_VOICE_ADSR_RR |
            SPU_VOICE_ADSR_SL
    );
    spu_voice_attr.voice = voice_channel;
    spu_voice_attr.volume.left = 0x1fff;
    spu_voice_attr.volume.right = 0x1fff;
    spu_voice_attr.pitch = 0x1000;
    spu_voice_attr.addr = vag_spu_addr;
    spu_voice_attr.a_mode = SPU_VOICE_LINEARIncN;
    spu_voice_attr.s_mode = SPU_VOICE_LINEARIncN;
    spu_voice_attr.r_mode = SPU_VOICE_LINEARIncN;
    spu_voice_attr.ar = 0x0;
    spu_voice_attr.dr = 0x0;
    spu_voice_attr.sr = 0x0;
    spu_voice_attr.rr = 0x0;
    spu_voice_attr.sl = 0xf;
    SpuSetVoiceAttr(&spu_voice_attr);
}

