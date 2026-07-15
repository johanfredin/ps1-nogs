#include "Frames.h"

#include "../lib/Heap.h"
#include "../lib/Log.h"

#define LOGR_LOG_TELEPORT(level, teleport)                      \
    LOG_DEBUG("*********************");                         \
    LOG_DEBUG("*   Teleport        *");                         \
    LOG_DEBUG("*********************");                         \
    LOG_DEBUG("x=%d", (&(teleport))->origin.x);                 \
    LOG_DEBUG("y=%d", (&(teleport))->origin.y);                 \
    LOG_DEBUG("w=%d", (&(teleport))->origin.w);                 \
    LOG_DEBUG("h=%d", (&(teleport))->origin.h);                 \
    LOG_DEBUG("dest_x=%d", (&(teleport))->dest_x);              \
    LOG_DEBUG("dest_y=%d", (&(teleport))->dest_y);              \
    LOG_DEBUG("dest_frame=%d", (&(teleport))->dest_frame)

void insert_beginning(SpriteLayer **root, SpriteLayer *new_layer) {
    new_layer->next = *root;
    *root = new_layer;
}

void insert_after(SpriteLayer *layer, SpriteLayer *new_layer) {
    new_layer->next = layer->next;
    layer->next = new_layer;
}

void frames_insert_sl_sorted(SpriteLayer **root, SpriteLayer *new_layer) {
    SpriteLayer *curr;
    if (*root == NULL || (*root)->prio >= new_layer->prio) {
        insert_beginning(root, new_layer);
        return;
    }

    for (curr = *root; curr->next != NULL; curr = curr->next) {
        if (curr->next->prio >= new_layer->prio) {
            break;
        }
    }
    insert_after(curr, new_layer);
}

FR_TileSet *frames_malloc_fr_tileset() {
    return Heap_Malloc(sizeof(FR_TileSet));
}
