#include "sys/types.h"

#include <libcd.h>
#include <malloc.h>

#include "CD.h"
#include "Heap.h"
#include "Logger.h"
#include "StrUtils.h"
#include "stdlib.h"

#define VALID_DA_START_TRACK 2
#define DA_MODE_REPEAT 2
#define DA_STOP 0
#define DA_ENABLED 1


void CD_Init(void) {
    if (CdInit()) {
        logr_log(INFO, "CD.c", "cd_init", "LIBCD initialized");
        return;
    }
    logr_log(ERROR, "CD.c", "cd_init", "LIBCD not initialized properly, terminating..."); \
    exit(1);
}

void CD_Free(CdData *p) {
    heap_free(p->file);
    heap_free(p);
}

CdData *CD_DataMalloc(char *name) {
    CdData *cd_data = heap_calloc(1, sizeof(CdData));
    cd_data->name = name;
    CD_AcquireData(cd_data);
    return cd_data;
}

CdData *CD_Find(char *name, CdData **assets, const uint8_t assets_cnt) {
    for (int i = 0; i < assets_cnt; i++) {
        if (STR_EQ(assets[i]->name, name)) {
            logr_log(TRACE, "CD.c", "cd_find", "Name=%s, found at index=%d", assets[i]->name, i);
            return assets[i];
        }
    }
    logr_log(ERROR, "CD.c", "cd_find", "No CdData with name='%s' in passed in array, terminating...", name);
    exit(1);
}

void CD_AcquireData(CdData *cd_data) {
    char file_path_raw[16];

    // Get raw file path
    strcpy(file_path_raw, "\\");
    strcat(file_path_raw, cd_data->name);
    strcat(file_path_raw, ";1");
    logr_log(DEBUG, "CD.c", "cd_acquire_data", "Loading file from CD: %s", file_path_raw);

    // Search for file on disc
    CdlFILE file_pos;
    if (CdSearchFile(&file_pos, file_path_raw) == NULL) {
        logr_log(ERROR, "CD.c", "cd_acquire_data", "File=%s not found, terminating...", cd_data->name);
        exit(1);
    }

    logr_log(TRACE, "CD.c", "cd_acquire_data", "file found");
    logr_log(TRACE, "CD.c", "cd_acquire_data", "file size: %d", file_pos.size);
    const int32_t num_secs = (int32_t)(file_pos.size + (CD_SECTOR - 1)) / CD_SECTOR;
    logr_log(TRACE, "CD.c", "cd_acquire_data", "seconds in: %d", num_secs);
    CdControl(CdlSetloc, (u_char *) &file_pos.pos, 0);
    unsigned long *buff = heap_malloc(CD_SECTOR * num_secs);
    CdRead(num_secs, buff, CdlModeSpeed);
    CdReadSync(0, 0);

    cd_data->file = buff;
    cd_data->sectors = num_secs;
    logr_log(INFO, "CD.c", "cd_acquire_data", "File %s loaded from CD", cd_data->name);
}

void CD_PlayDATrack(CdDATrack *track) {
#if DA_ENABLED
    /*
     * Do not attempt to play a track that is already playing or is not a valid DA track no (0-1 = DATA)
     */
    const uint8_t cant_play = ((track == NULL) | track->is_playing | track->track < VALID_DA_START_TRACK);
    if (cant_play) {
        return;
    }

    int32_t t[] = {track->track, 0};
    CdPlay(DA_MODE_REPEAT, t, 0);
    track->is_playing = 1;
#endif
}

void CD_StopDATrack(CdDATrack *track) {
#if DA_ENABLED
    /*
     * Do not attempt to stop a track that is not playing or is not a valid DA track no (0-1 = DATA)
     */
    const uint8_t cant_stop = (track == NULL) | !track->is_playing | track->track < VALID_DA_START_TRACK;
    if (cant_stop) {
        return;
    }

    int32_t t[] = {track->track, 0};
    track->is_playing = CdPlay(DA_STOP, t, 0);
    track->is_playing = 0;
#endif
}

void CD_SwapDATrack(CdDATrack *from, CdDATrack *to) {
#if DA_ENABLED
    const uint8_t from_track_nr = from->track;
    const uint8_t to_track_nr = to->track;

    if (from_track_nr == to_track_nr) {
        // If the track we want to swap to is the same track, do nothing
        return;
    }

    CD_StopDATrack(from);
    CD_PlayDATrack(to);
#endif
}
