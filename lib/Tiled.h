#ifndef PSX_SPIKE_TILED_H
#define PSX_SPIKE_TILED_H

#include <stdbool.h>
#include <stdint.h>

#include "JSONParser.h"

typedef struct ObjectLayer_Bounds {
    uint32_t width, height;
    uint32_t id;
    uint32_t x, y;
    bool visible;
    struct ObjectLayer_Bounds *next;
} ObjectLayer_Bounds;

typedef struct ObjectLayer_Teleport {
    uint32_t width, height;
    uint32_t id;
    uint32_t x, y;
    int16_t dest_x, dest_y;
    bool visible;
    uint8_t dest_frame;
    struct ObjectLayer_Teleport *next;
} ObjectLayer_Teleport;

typedef struct ObjectLayer_Dialog {
    uint32_t width, height;
    uint32_t id;
    uint32_t x, y;
    size_t n_lines;
    uint16_t max_chars;
    char *text;
    bool visible;
    struct ObjectLayer_Dialog *next;
} ObjectLayer_Dialog;

typedef struct Layer_Data {
    uint16_t id;
    struct Layer_Data *next;
} Layer_Data;

typedef struct Tile_Set {
    uint16_t firstgid;
    char *source;
    struct Tile_Set *next;
} Tile_Set;

typedef struct Tile_Layer {
    uint16_t height, width, id, x, y, prio, active_sprites_cnt;
    char *name, *type, *layer_type;
    bool visible;
    Layer_Data *data;
    struct Tile_Layer *next;
} Tile_Layer;

typedef struct Tile_Map {
    // Map width in n_tiles (not in pixels)
    uint16_t width;
    // Map height in n_tiles (not in pixels)
    uint16_t height;
    // Map tile width in pixels
    uint16_t tile_width;
    // Map tile height in pixels
    uint16_t tile_height;
    // Pointer to linked list of tile layers
    Tile_Layer *layers;
    // Pointer to linked list of bounds
    ObjectLayer_Bounds *bounds;
    // Pointer to linked list of teleports
    ObjectLayer_Teleport *teleports;
    // Pointer to linked list of dialogs
    ObjectLayer_Dialog *dialogs;
    // Pointer to linked list of tilesets
    Tile_Set *tile_sets;

    uint8_t bounds_cnt, layers_cnt, teleports_cnt, tilesets_cnt, dialogs_cnt;
} TileMap;


/**
 * Populates a new Tile_Map type from JSON data received. This function allocates
 * memory and must be either freed manually or by calling #tiled_free
 * @param root root entry in the JSON Data linked list
 * @return a Tile_Map struct allocated on the heap.
 */
TileMap *Tiled_FromJSON(const JSON_Data *root);

void Tiled_Print(uint8_t level, const TileMap *map);

/**
 * Frees all the allocated memory in linked list passed in.
 * @param tm entry of linked list
 */
void Tiled_Destroy(TileMap *tm);

#endif //PSX_SPIKE_TILED_H
