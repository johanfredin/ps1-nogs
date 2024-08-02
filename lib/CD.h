/**
 * Helper lib for streaming data from the cd rom
 */
#ifndef PSX_CD_READER_H
#define PSX_CD_READER_H

#define CD_SECTOR 0x800

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

void cd_init();
void cd_data_init(CdData *p, char *name);
CdData *cd_data_malloc(char *name);
void cd_data_free(CdData *p);

CdData *cd_find(char *name, CdData **assets, unsigned char assets_cnt);

void cd_acquire_data(CdData *cd_data);

void cd_da_play(CdDATrack *track);
void cd_da_stop(CdDATrack *track);
void cd_da_swap(CdDATrack *from, CdDATrack *to);

#endif // PSX_CD_READER_H
