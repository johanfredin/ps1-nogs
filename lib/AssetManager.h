#ifndef PSX_ASSET_MANAGER_H
#define PSX_ASSET_MANAGER_H

#include "libgpu.h"

#include "CD.h"

#define ASSETMANAGER_SOUND_MALLOC_MAX 0xA
#define ASSETMANAGER_VAG_HEADER_BYTE_SIZE 0x30
#define ASSETMANAGER_BLEND_NORMAL 128

#define ASSETMANAGER_HAS_CLUT(tim) ((tim)->pmode & 3) < 2

#define ASSETMANAGER_AUDIO_PLAY(voice_channel) SpuSetKey(SpuOn, voice_channel)
#define ASSETMANAGER_SET_BLEND(p) (p)->r = (p)->g = (p) -> b = ASMG_BLEND_NORMAL
#define ASSETMANAGER_SET_RGB(p, cr, cg, cb) (p)->r = cr; (p)->g = cg; (p)->b = cb

/**
 * All VAGs have a 48 byte header, which must be removed for playback. This header should not be removed
 * before converting VAGs to VABs on the Mac or PC; otherwise, improper conversion will occur.
 */
#define ASSETMANAGER_AUDIO_SKIP_VAG_HEADER(vag) ((vag) += ASSETMANAGER_VAG_HEADER_BYTE_SIZE)

void AssetManager_LoadTIMData(TIM_IMAGE *tim_data, const CdData *cd_data);
void AssetManager_LoadSprite(SPRT *sprt, TIM_IMAGE *tim, const CdData *cd_data);
void AssetManager_LoadPolyFT4(POLY_FT4 *poly_ft4, TIM_IMAGE *tim, const CdData *cd_data);
void AssetManager_AudioInit(void);
void AssetManager_TransferVAGToSPU(const CdData *cd_data, u_long voice_channel);

#endif // PSX_ASSET_MANAGER_H
