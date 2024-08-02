#ifndef PSX_ASSET_MANAGER_H
#define PSX_ASSET_MANAGER_H

#include "sys/types.h"
#include "libgpu.h"

#include "CD.h"

#define ASMG_SOUND_MALLOC_MAX 0xA
#define ASMG_VAG_HEADER_BYTE_SIZE 0x30
#define ASMG_BLEND_NORMAL 128

#define ASMG_HAS_CLUT(gs_image) ((gs_image)->pmode & 3) < 2

#define ASMG_AUDIO_PLAY(voice_channel) SpuSetKey(SpuOn, voice_channel)
#define ASMG_SET_BLEND(p) (p)->r = (p)->g = (p) -> b = ASMG_BLEND_NORMAL
#define ASMG_SET_RGB(p, cr, cg, cb) (p)->r = cr; (p)->g = cg; (p)->b = cb

/**
 * All VAGs have a 48 byte header, which must be removed for playback. This header should not be removed
 * before converting VAGs to VABs on the Mac or PC; otherwise, improper conversion will occur.
 */
#define ASMG_AUDIO_SKIP_VAG_HEADER(vag) ((vag) += ASMG_VAG_HEADER_BYTE_SIZE)

void asmg_load_tim_data(TIM_IMAGE *tim_data, CdData *cdr_data);
void asmg_load_sprt(SPRT *sprt, TIM_IMAGE *tim, CdData *data);
void asmg_load_poly_ft4(POLY_FT4 *poly_ft4, TIM_IMAGE *tim, CdData *cdr_data);
void asmg_audio_init();
void asmg_transfer_vag_to_spu(CdData *cdr_data, u_long voice_channel);

#endif // PSX_ASSET_MANAGER_H
