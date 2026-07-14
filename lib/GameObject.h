#ifndef PSX_GAME_OBJECT_H
#define PSX_GAME_OBJECT_H

#include <stdint.h>

#include "libgpu.h"

#define GAMEOBJECT_TYPE_PLAYER 0x0
#define GAMEOBJECT_TYPE_NPC 0x1

#define GAMEOBJECT_HEADING_NONE 0x0
#define GAMEOBJECT_HEADING_UP 0x1
#define GAMEOBJECT_HEADING_DOWN 0x2
#define GAMEOBJECT_HEADING_LEFT 0x4
#define GAMEOBJECT_HEADING_RIGHT 0x8

typedef struct GameObject {
    void *prim;
    RECT *bounds;
    int16_t old_x, old_y;
    int16_t x_speed, y_speed;
    uint16_t w, h;
    uint8_t health: 7;
    uint8_t can_move: 1;
    uint8_t x, y;
    uint8_t heading;
} GameObject;


typedef struct Camera {
    int16_t x, y;
    uint16_t viewport_w, viewport_h;
    uint16_t map_w, map_h;
    GameObject *obj_in_focus;
} Camera;

#define GAMEOBJECT_SWITCH_DIR(gameobject)   \
    (gameobject)->x_speed *= -1;      \
    (gameobject)->y_speed *= -1

#define GAMEOBJECT_SWITCH_X_DIR(gameobject) ((gameobject)->x_speed *= -1)
#define GAMEOBJECT_SWITCH_Y_DIR(gameobject) ((gameobject)->y_speed *= -1)

#define GAMEOBJECT_IS_MOVING(gameobject) ((gameobject)->heading | GAMEOBJECT_HEADING_NONE)

#define GAMEOBJECT_IS_HEADING_RIGHT(gameobject) ((gameobject)->heading & GAMEOBJECT_HEADING_RIGHT)
#define GAMEOBJECT_IS_HEADING_LEFT(gameobject) ((gameobject)->heading & GAMEOBJECT_HEADING_LEFT)
#define GAMEOBJECT_IS_HEADING_UP(gameobject) ((gameobject)->heading & GAMEOBJECT_HEADING_UP)
#define GAMEOBJECT_IS_HEADING_DOWN(gameobject) ((gameobject)->heading & GAMEOBJECT_HEADING_DOWN)

#define GAMEOBJECT_ANIM_CYCLE_COMPLETE(anim) anim->acc_ticks >= (anim)->ticks_per_frame

#define GAMEOBJECT_IS_NOT_MOVING(gameobject) !GAMEOBJECT_IS_MOVING(gameobject)


void GameObject_Init(GameObject *gameobject, RECT *bounds, void *prim, uint16_t spawn_x, uint16_t spawn_y, int16_t w, int16_t h, int16_t x_speed, int16_t y_speed, uint8_t health);
/**
 * Draw the game object
 * @param game_object the game object image to draw
 */
void GameObject_Draw(GameObject *game_object);

/**
 * Update the game object
 * @param player how to interact with player
 */
void GameObject_Tick(GameObject *player);

void GameObject_CameraInit(Camera *cam, GameObject *obj_in_focus);
void GameObject_CameraTick(Camera *cam);

#endif // PSX_GAME_OBJECT_H
