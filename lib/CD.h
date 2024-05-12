/**
 * Helper lib for streaming data from the cd rom
 */
#ifndef PSX_CD_READER_H
#define PSX_CD_READER_H

#include <stdint-gcc.h>

#define CD_SECTOR 0x800

typedef struct CdData {
    char *name;
    u_long *file;
    u_int sectors;
} CdData;

typedef struct CdDATrack {
    u_char track: 7;
    u_char is_playing: 1;
} CdDATrack;

void cd_init();
void cd_data_init(CdData *p, char *name);

CdData *cd_find(char *name, CdData **assets, uint8_t assets_cnt);

void cd_acquire_data(CdData *cd_data);

void cd_da_play(CdDATrack *track);
void cd_da_stop(CdDATrack *track);
void cd_da_swap(CdDATrack *from, CdDATrack *to);

#endif // PSX_CD_READER_H
