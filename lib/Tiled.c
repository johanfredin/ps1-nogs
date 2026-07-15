#include "stdlib.h"
#include "Tiled.h"

#include "Heap.h"
#include "Log.h"
#include "stdio.h"
#include "StrUtils.h"

/**
 * Make sure that passed in key=&quot;name&quot;<br>
 * Make sure that passed in val=&quot;value&quot;
 * @param key key to check
 * @param val value to check
 */
#define TILED_VALIDATE_PROP(key, val)                                                                                           \
if (STR_NEQ(key, "name")) {                                                                                                     \
    LOG_ERR("property key='name' expected here, instead was=%s, exiting...", key);    \
    exit(1);                                                                                                                    \
}                                                                                                                               \
if (STR_NEQ(val, "value")) {                                                                                                    \
    LOG_ERR("property key='value' expected here, instead was='%s', exiting...", val); \
    exit(1);                                                                                                                    \
}

static void add_tile_layers_to_map(TileMap *tm, JSON_Data *jobj_root);
static void add_data_to_layer(Tile_Layer *layer, JSON_Data *root);
static void add_additional_properties_to_layer(Tile_Layer *layer, const JSON_Data *root);
static void add_tile_sets_to_map(TileMap *tm, JSON_Data *root);
static void add_object_layers_to_map(TileMap *tm, JSON_Data *root);
static void add_teleport_layers_to_map(TileMap *tm, JSON_Data *root);
static void add_dialog_layers_to_map(TileMap *tm, JSON_Data *root);
static TileMap *malloc_tile_map();


TileMap *Tiled_FromJSON(const JSON_Data *root) {
    if (root == NULL) {
        LOG_ERR("root is NULL");
        exit(1);
    }
    TileMap *tm = malloc_tile_map();
    for (const JSON_Data *curr = root; curr != NULL; curr = curr->next) {
        char *key = curr->key;
        void *value = curr->value;
        if (STR_EQ(key, "height")) {
            tm->height = *(int *) value;
        } else if (STR_EQ(key, "width")) {
            tm->width = *(int *) value;
        } else if (STR_EQ(key, "tileheight")) {
            tm->tile_height = *(int *) value;
        } else if (STR_EQ(key, "tilewidth")) {
            tm->tile_width = *(int *) value;
        } else if (STR_EQ(key, "layers")) {
            add_tile_layers_to_map(tm, value);
        } else if (STR_EQ(key, "tilesets")) {
            add_tile_sets_to_map(tm, value);
        }
    }
    return tm;
}

static TileMap *malloc_tile_map() {
    return Heap_Malloc(sizeof(TileMap));
}

void Tiled_Destroy(TileMap *tm) {
    while (tm->layers != NULL) {
        Tile_Layer *aux = tm->layers;
        tm->layers = tm->layers->next;
        HEAP_FREE_LINKED_LIST(aux->data, Layer_Data);
        Heap_Free(aux);
    }
    Heap_Free(tm->layers);
    HEAP_FREE_LINKED_LIST(tm->bounds, ObjectLayer_Bounds)
    HEAP_FREE_LINKED_LIST(tm->teleports, ObjectLayer_Teleport)
    HEAP_FREE_LINKED_LIST(tm->dialogs, ObjectLayer_Dialog)
    HEAP_FREE_LINKED_LIST(tm->tile_sets, Tile_Set)
    Heap_Free(tm);
}

void Tiled_Print(const uint8_t level, const TileMap *map) {
    LOG_INFO("Map parsed from JSON");
    LOG_INFO("-------------------- ");
    LOG_INFO("{ ");
    LOG_INFO("  bounds_cnt=%d", map->bounds_cnt);
    LOG_INFO("  teleports_cnt=%d", map->teleports_cnt);
    LOG_INFO("  tilesets_cnt=%d", map->tilesets_cnt);
    LOG_INFO("  width=%d ", map->width);
    LOG_INFO("  height=%d ", map->height);
    LOG_INFO("  tile_width=%d ", map->tile_width);
    LOG_INFO("  tile_height=%d ", map->tile_height);
    LOG_INFO("  layers_cnt=%d ", map->layers_cnt);
    LOG_INFO("  layers=[ ");
    for (const Tile_Layer *tile_layer = map->layers; tile_layer; tile_layer = tile_layer->next) {
        LOG_INFO("    { ");
        LOG_INFO("      name=%s ", tile_layer->name);
        LOG_INFO("      type=%s ", tile_layer->type);
        LOG_INFO("      id=%d ", tile_layer->id);
        LOG_INFO("      x=%d ", tile_layer->x);
        LOG_INFO("      y=%d ", tile_layer->y);
        LOG_INFO("      width=%d ", tile_layer->width);
        LOG_INFO("      height=%d ", tile_layer->height);
        LOG_INFO("      visible=%d ", tile_layer->visible);
        LOG_INFO("      layer_type=%s ", tile_layer->layer_type);
        LOG_INFO("      prio=%d ", tile_layer->prio);
        LOG_INFO("      active_sprites_cnt=%d ", tile_layer->active_sprites_cnt);
        LOG_INFO("    } ");
    }
    LOG_INFO("  ] ");
    LOG_INFO("  bounds=[ ");
    for (ObjectLayer_Bounds *bounds_layer = map->bounds; bounds_layer; bounds_layer = bounds_layer->next) {
        LOG_INFO("    { ");
        LOG_INFO("      id=%d ", bounds_layer->id);
        LOG_INFO("      visible=%d ", bounds_layer->visible);
        LOG_INFO("      x=%d ", bounds_layer->x);
        LOG_INFO("      y=%d ", bounds_layer->y);
        LOG_INFO("      width=%d ", bounds_layer->width);
        LOG_INFO("      height=%d ", bounds_layer->height);
        LOG_INFO("      visible=%d ", bounds_layer->visible);
        LOG_INFO("    } ");
    }
    LOG_INFO("  ] ");
    LOG_INFO("  teleports=[ ");
    for (const ObjectLayer_Teleport *teleports_layer = map->teleports; teleports_layer; teleports_layer = teleports_layer->next) {
        LOG_INFO("    { ");
        LOG_INFO("      id=%d ", teleports_layer->id);
        LOG_INFO("      visible=%d ", teleports_layer->visible);
        LOG_INFO("      x=%d ", teleports_layer->x);
        LOG_INFO("      y=%d ", teleports_layer->y);
        LOG_INFO("      width=%d ", teleports_layer->width);
        LOG_INFO("      height=%d ", teleports_layer->height);
        LOG_INFO("      dest_frame=%d ", teleports_layer->dest_frame);
        LOG_INFO("      dest_x=%d ", teleports_layer->dest_x);
        LOG_INFO("      dest_y=%d ", teleports_layer->dest_y);
        LOG_INFO("    } ");
    }
    LOG_INFO("  ] ");
    LOG_INFO("  dialogs=[ ");
    for (const ObjectLayer_Dialog *dialog_layer = map->dialogs; dialog_layer; dialog_layer = dialog_layer->next) {
        LOG_INFO("    { ");
        LOG_INFO("      id=%d ", dialog_layer->id);
        LOG_INFO("      visible=%d ", dialog_layer->visible);
        LOG_INFO("      x=%d ", dialog_layer->x);
        LOG_INFO("      y=%d ", dialog_layer->y);
        LOG_INFO("      width=%d ", dialog_layer->width);
        LOG_INFO("      height=%d ", dialog_layer->height);
        LOG_INFO("      text=%s ", dialog_layer->text);
        LOG_INFO("      max_chars=%d ", dialog_layer->max_chars);
        LOG_INFO("      n_lines=%d ", dialog_layer->n_lines);
        LOG_INFO("    } ");
    }
    LOG_INFO("  ] ");
    LOG_INFO("  tile_sets=[ ");
    for (const Tile_Set *tile_set = map->tile_sets; tile_set; tile_set = tile_set->next) {
        LOG_INFO("    { ");
        LOG_INFO("       firstgid: %d", tile_set->firstgid);
        LOG_INFO("       source: %s", tile_set->source);
        LOG_INFO("    } ");
    }
    LOG_INFO("  ] ");
    LOG_INFO("} ");
}

static void add_tile_layers_to_map(TileMap *tm, JSON_Data *jobj_root) {
    Tile_Layer *tl_root = Heap_Malloc(sizeof(Tile_Layer));
    uint8_t layers_cnt = 1; // We have already encountered a layer if we're in here so at least we know there is one.
    JSON_Data *jobj_curr;
    Tile_Layer *tl_curr, *tl_prev;

    for (jobj_curr = jobj_root, tl_curr = tl_root; jobj_curr != NULL; jobj_curr = jobj_curr->next) {
        Tile_Layer *next = NULL;
        for (JSON_Data *curr_layer = jobj_curr->value; curr_layer != NULL; curr_layer = curr_layer->next) {
            char *key = curr_layer->key;
            void *value = curr_layer->value;

            if (STR_EQ(key, "data")) {
                add_data_to_layer(tl_curr, value);
            } else if (STR_EQ(key, "height")) {
                tl_curr->height = *(uint16_t *) value;
            } else if (STR_EQ(key, "id")) {
                tl_curr->id = *(uint16_t *) value;
            } else if (STR_EQ(key, "name")) {
                const bool is_bounds = STR_EQ((char *) value, "bounds");
                const bool is_teleports = STR_EQ((char *) value, "teleports");
                const bool is_dialogs = STR_EQ((char *) value, "dialogs");
                if (is_bounds | is_teleports | is_dialogs) {
                    // FF until we reach objects array
                    while (STR_NEQ(curr_layer->key, "objects")) {
                        curr_layer = curr_layer->next;
                    }
                }
                // Value should now be at objects root
                value = curr_layer->value; // Sync
                if (is_bounds) {
                    add_object_layers_to_map(tm, value);
                    Heap_Free(tl_curr);
                    tl_curr = tl_prev;
                } else if (is_teleports) {
                    add_teleport_layers_to_map(tm, value);
                    Heap_Free(tl_curr);
                    tl_curr = tl_prev;
                } else if (is_dialogs) {
                    add_dialog_layers_to_map(tm, value);
                    Heap_Free(tl_curr);
                    tl_curr = tl_prev;
                } else {
                    tl_curr->name = (char *) value;
                }
            } else if (STR_EQ(key, "type")) {
                tl_curr->type = (char *) value;
            } else if (STR_EQ(key, "visible")) {
                tl_curr->visible = *(uint8_t *) value;
            } else if (STR_EQ(key, "width")) {
                tl_curr->width = *(uint16_t *) value;
            } else if (STR_EQ(key, "x")) {
                tl_curr->x = *(uint16_t *) value;
            } else if (STR_EQ(key, "y")) {
                tl_curr->y = *(uint16_t *) value;
            } else if (STR_EQ(key, "properties")) {
                add_additional_properties_to_layer(tl_curr, value);
            }
        }

        if (jobj_curr->next != NULL) {
            layers_cnt++;
            next = Heap_Malloc(sizeof(Tile_Layer));
        }
        tl_curr->next = next;
        tl_prev = tl_curr;
        tl_curr = next;
    }
    tm->layers = tl_root;
    tm->layers_cnt = layers_cnt;
}

static void add_object_layers_to_map(TileMap *tm, JSON_Data *root) {
    size_t objects_cnt;
    JSON_Data *curr_obj_layer; // Our current JSON object being iterated
    ObjectLayer_Bounds *ol_root = Heap_Malloc(sizeof(ObjectLayer_Bounds));
    ObjectLayer_Bounds *ol_curr = ol_root;
    for (curr_obj_layer = root, objects_cnt = 0;
         curr_obj_layer != NULL;
         curr_obj_layer = curr_obj_layer->next, objects_cnt++
    ) {
        // Iterate objects
        const JSON_Data *entry_root = curr_obj_layer->value;
        for (const JSON_Data *entry_curr = entry_root;
             entry_curr != NULL; entry_curr = entry_curr->next) {
            // Iterate object properties
            char *key = entry_curr->key;
            void *value = entry_curr->value;

            if (STR_EQ(key, "height")) {
                ol_curr->height = *(uint32_t *) value;
            } else if (STR_EQ(key, "id")) {
                ol_curr->id = *(uint32_t *) value;
            } else if (STR_EQ(key, "visible")) {
                ol_curr->visible = *(uint8_t *) value;
            } else if (STR_EQ(key, "width")) {
                ol_curr->width = *(uint32_t *) value;
            } else if (STR_EQ(key, "x")) {
                ol_curr->x = *(uint32_t *) value;
            } else if (STR_EQ(key, "y")) {
                ol_curr->y = *(uint32_t *) value;
            }
        }
        HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(curr_obj_layer, ol_curr, ObjectLayer_Bounds)
    }
    tm->bounds = ol_root;
    tm->bounds_cnt = objects_cnt;
}

static void add_teleport_layers_to_map(TileMap *tm, JSON_Data *root) {
    size_t objects_cnt;
    JSON_Data *curr_obj_layer; // Our current JSON object being iterated
    ObjectLayer_Teleport *ol_root = Heap_Malloc(sizeof(ObjectLayer_Teleport));
    ObjectLayer_Teleport *ol_curr = ol_root;
    for (
        curr_obj_layer = root, objects_cnt = 0;
        curr_obj_layer != NULL;
        curr_obj_layer = curr_obj_layer->next, objects_cnt++
    ) {
        const JSON_Data *entry_root = curr_obj_layer->value;
        for (const JSON_Data *entry_curr = entry_root; entry_curr != NULL; entry_curr = entry_curr->next) {
            // Iterate object properties
            char *key = entry_curr->key;
            void *value = entry_curr->value;

            if (STR_EQ(key, "height")) {
                ol_curr->height = *(uint32_t *) value;
            } else if (STR_EQ(key, "id")) {
                ol_curr->id = *(uint32_t *) value;
            } else if (STR_EQ(key, "visible")) {
                ol_curr->visible = *(uint8_t *) value;
            } else if (STR_EQ(key, "width")) {
                ol_curr->width = *(uint32_t *) value;
            } else if (STR_EQ(key, "x")) {
                ol_curr->x = *(uint32_t *) value;
            } else if (STR_EQ(key, "y")) {
                ol_curr->y = *(uint32_t *) value;
            } else if (STR_EQ(key, "properties")) {
                JSON_Data *props_root = entry_curr->value;

                // Init dest properties to 0 to prevent garbage
                ol_curr->dest_x = 0;
                ol_curr->dest_y = 0;
                ol_curr->dest_frame = 0;

                for (const JSON_Data *props_curr = props_root; props_curr != NULL; props_curr = props_curr->next) {
                    JSON_Data *teleport_property_obj = props_curr->value;
                    char *prop_name = teleport_property_obj->value;
                    const short prop_value = *(short *) teleport_property_obj->next->next->value;

                    TILED_VALIDATE_PROP(teleport_property_obj->key, teleport_property_obj->next->next->key)

                    if (STR_EQ(prop_name, "dest_frame")) {
                        ol_curr->dest_frame = prop_value;
                    } else if (STR_EQ(prop_name, "dest_x")) {
                        ol_curr->dest_x = prop_value;
                    } else if (STR_EQ(prop_name, "dest_y")) {
                        ol_curr->dest_y = prop_value;
                    }
                }
            }
        }
        HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(curr_obj_layer, ol_curr, ObjectLayer_Teleport)
    }
    tm->teleports = ol_root;
    tm->teleports_cnt = objects_cnt;
}

static void add_dialog_layers_to_map(TileMap *tm, JSON_Data *root) {
    size_t objects_cnt;
    JSON_Data *curr_obj_layer; // Our current json object being iterated
    ObjectLayer_Dialog *ol_root = Heap_Malloc(sizeof(ObjectLayer_Dialog));
    ObjectLayer_Dialog *ol_curr = ol_root;
    for (curr_obj_layer = root, objects_cnt = 0;
         curr_obj_layer != NULL;
         curr_obj_layer = curr_obj_layer->next,
         objects_cnt++
    ) {
        const JSON_Data *entry_root = curr_obj_layer->value;
        for (const JSON_Data *entry_curr = entry_root; entry_curr != NULL; entry_curr = entry_curr->next) {
            // Iterate object properties
            char *key = entry_curr->key;
            void *value = entry_curr->value;

            if (STR_EQ(key, "height")) {
                ol_curr->height = *(uint32_t *) value;
            } else if (STR_EQ(key, "id")) {
                ol_curr->id = *(uint32_t *) value;
            } else if (STR_EQ(key, "visible")) {
                ol_curr->visible = *(uint8_t *) value;
            } else if (STR_EQ(key, "width")) {
                ol_curr->width = *(uint32_t *) value;
            } else if (STR_EQ(key, "x")) {
                ol_curr->x = *(uint32_t *) value;
            } else if (STR_EQ(key, "y")) {
                ol_curr->y = *(uint32_t *) value;
            } else if (STR_EQ(key, "properties")) {
                // Init dest properties to prevent garbage
                ol_curr->text = NULL;
                ol_curr->max_chars = 0;
                ol_curr->n_lines = 1;

                JSON_Data *props_root = entry_curr->value;
                for (const JSON_Data *props_curr = props_root; props_curr != NULL; props_curr = props_curr->next) {
                    JSON_Data *teleport_property_obj = props_curr->value;
                    char *prop_name = teleport_property_obj->value;
                    void *prop_value = teleport_property_obj->next->next->value;

                    TILED_VALIDATE_PROP(teleport_property_obj->key, teleport_property_obj->next->next->key)

                    if (STR_EQ(prop_name, "max_chars")) {
                        ol_curr->max_chars = *(uint16_t *) prop_value;
                    } else if (STR_EQ(prop_name, "n_lines")) {
                        ol_curr->n_lines = *(uint8_t *) prop_value;
                    } else if (STR_EQ(prop_name, "text")) {
                        ol_curr->text = (char *) prop_value;
                    }
                }
            }
        }
        HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(curr_obj_layer, ol_curr, ObjectLayer_Dialog)
    }
    tm->dialogs = ol_root;
    tm->dialogs_cnt = objects_cnt;
}

static void add_additional_properties_to_layer(Tile_Layer *layer, const JSON_Data *root) {
    // Iterate properties array
    for (const JSON_Data *curr = root; curr != NULL; curr = curr->next) {
        JSON_Data *curr_props = curr->value;

        // Fetch the 2 properties needed in json object
        char *prop_name = curr_props->value;
        void *prop_value = curr_props->next->next->value;

        // Validate that the property prop_value is actually 2 lanes down
        TILED_VALIDATE_PROP(curr_props->key, curr_props->next->next->key)

        if (STR_EQ(prop_name, "layer_type")) {
            layer->layer_type = (char *) prop_value;
        } else if (STR_EQ(prop_name, "prio")) {
            layer->prio = *(uint16_t *) prop_value;
        }
    }
}

static void add_data_to_layer(Tile_Layer *layer, JSON_Data *root) {
    Layer_Data *data_root = Heap_Malloc(sizeof(Layer_Data));
    uint16_t active_sprites_cnt = 0;
    Layer_Data *data = data_root;
    for (const JSON_Data *curr = root; curr != NULL; curr = curr->next) {
        data->id = *(uint16_t *) curr->value;
        if (data->id > 0) {
            active_sprites_cnt++;
        }
        HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(curr, data, Layer_Data)
    }
    layer->active_sprites_cnt = active_sprites_cnt;
    layer->data = data_root;
}

static void add_tile_sets_to_map(TileMap *tm, JSON_Data *root) {
    size_t tilesets_cnt;
    JSON_Data *json_curr;
    Tile_Set *ts_root = Heap_Malloc(sizeof(Tile_Set));
    Tile_Set *ts_curr = ts_root;
    for (
        json_curr = root, tilesets_cnt = 0;
        json_curr != NULL;
        json_curr = json_curr->next, tilesets_cnt++
    ) {
        for (JSON_Data *json_tileset = json_curr->value; json_tileset != NULL;
             json_tileset = json_tileset->next) {
            if (STR_EQ(json_tileset->key, "firstgid")) {
                ts_curr->firstgid = *(uint16_t *) json_tileset->value;
            } else if (STR_EQ(json_tileset->key, "source")) {
                ts_curr->source = (char *) json_tileset->value;
            }
        }
        HEAP_ALLOC_NEW_LINKEDLIST_ENTRY_IF_MORE_DATA(json_curr, ts_curr, Tile_Set)
    }
    tm->tilesets_cnt = tilesets_cnt;
    tm->tile_sets = ts_root;
}
