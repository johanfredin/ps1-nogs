#ifndef PSX_FRAMES_H
#define PSX_FRAMES_H

#include "libgpu.h"
#include "libgs.h"

#include "GameObject.h"
#include "TextBox.h"

typedef struct Teleport {
    RECT origin;
    u_short dest_x, dest_y;
    // frame array index of frame to change to when colliding with this teleport
    uint8_t dest_frame;
} Teleport;

typedef struct CollisionBlock {
    // The actual physical bounds that we will collide with in the frame
    RECT *bounds;
    // The amount of blocks on one frame
    uint8_t amount;
} CollisionBlock;

typedef struct FR_Dialog {
    // If we collide with these bounds and press interact button then dialog can play (if not playing already)
    RECT bounds;
    uint16_t max_chars;
    uint8_t n_lines: 7;
    uint8_t initialized: 1;
    DlgBox *content;
} FR_Dialog;

typedef struct SpriteLayer {
    GsSPRITE **sprites;
    uint16_t sprites_cnt;
    uint16_t prio;
    struct SpriteLayer *next;
} SpriteLayer;

typedef struct FR_TileSet {
    char *source;
    uint16_t start_id;
    GsSPRITE *sprite;
    struct FR_TileSet *next;
} FR_TileSet;

typedef struct Frame {
    SpriteLayer *bg_layers, *fg_layers;
    uint8_t t_amount, d_amount, offset_x, offset_y;
    uint16_t width, height;
    CollisionBlock *collision_blocks;
    Teleport *teleports;
    FR_Dialog *dialogs;
    GameObject *game_object;
    FR_TileSet *fr_tilesets;
    CdDATrack *audio_track;
} Frame;

FR_TileSet *frames_malloc_fr_tileset();
void frames_insert_sl_sorted(SpriteLayer **root, SpriteLayer *new_layer);

#endif
