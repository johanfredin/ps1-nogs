//
// Created on 12/12/2021.
//

#ifndef PSX_DEV_TXTHANDLER_H
#define PSX_DEV_TXTHANDLER_H

#include <stdbool.h>

#include "../lib/AssetManager.h"

#define TXT_FNT_PADDING_DEFAULT 2

typedef struct Font {
    // Character width of font image
    uint8_t cw;
    // Character height of font image
    uint8_t ch;
    // Padding between characters
    uint8_t padding;
    // The image representing the whole font image
    SPRT *fnt_sprite;
} Font;

typedef struct Message {
    SPRT *fnt_sprites;
    uint16_t strlen;
    uint16_t acc_chars;
    uint8_t active: 4;
    uint8_t acc_ticks: 4;
} Message;

typedef struct Dialog {
    uint8_t n_messages;
    uint8_t x;
    uint8_t y;
    uint8_t ticks_per_frame: 7;
    bool visible: 1;
    char *id;
    Message *messages;
} Dialog;

/**
 * Load a font from cd and store on the heap.
 * @param name name of the font file e.g my_font.tim
 * @param cw Character width of font image
 * @param ch Character height of font image
 * @param padding Padding between characters
 * @return pointer to font from cd
 */
Font *txt_fnt_init(char *name, u_char cw, u_char ch, u_char padding);

Dialog *txt_dlg_init(char **strs, char *id, u_char n_messages, Font *fnt, u_short ticks_per_frame, u_char x, u_char y, u_char visible);
void *txt_msg_init(Message *msg, Font *font, u_char x, u_char y, char *str, u_char make_static, u_char active);
void txt_dlg_reset(Dialog *dlg);
void txt_msg_draw(Message *msg);
void txt_dlg_draw(Dialog *dlg);
void txt_dlg_tick(Dialog *dlg);
void txt_next_msg(Dialog *dlg, u_char can_skip);
u_char txt_dlg_complete(Dialog *dlg);

#endif //PSX_DEV_TXTHANDLER_H
