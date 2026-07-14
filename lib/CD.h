/**
 * Helper lib for streaming data from the cd rom
 */
#ifndef PSX_CD_READER_H
#define PSX_CD_READER_H

#define CD_SECTOR 0x800
#include <stdint.h>

/**
 * Represents a chunk of data on the cd. Data could be anything from a
 * TIM image, a text file or a VAG file. Using this struct requires using
 * heap allocation for the file pointer since I have not yet figured out
 * how to avoid that. It is perfectly possible to have the struct itself
 * stack or globally allocated but the file ptr must be heap. For convenience
 * there are the functions cd_data_malloc and cd_data_free that handles proper
 * allocation and freeing of a data asset.
 */
typedef struct CdData {
    // The name of the file on the CD
    char *name;
    // Pointer to the data itself within the file (must be heap allocated)
    unsigned long *file;
    // The amount of sectors this data chunk occupies
    unsigned long sectors;
} CdData;

typedef struct CdDATrack {
    unsigned char track: 7;
    unsigned char is_playing: 1;
} CdDATrack;

void CD_Init(void);
void CD_Free(CdData *p);
CdData *CD_DataMalloc(char *name);

CdData *CD_Find(char *name, CdData **assets, uint8_t assets_cnt);

void CD_AcquireData(CdData *cd_data);

void CD_PlayDATrack(CdDATrack *track);
void CD_StopDATrack(CdDATrack *track);
void CD_SwapDATrack(CdDATrack *from, CdDATrack *to);

#endif // PSX_CD_READER_H
