#include "GameObject.h"
#include "Log.h"
#include "GPU.h"
#include "stddef.h"
#include "stdio.h"

#define LOG_GOBJ(level, gobj)                  \
    LOG_DEBUG("*********************");             \
    LOG_DEBUG("*   Game Object     *");             \
    LOG_DEBUG("*********************");             \
    LOG_DEBUG("w=%d", (gobj)->w);                   \
    LOG_DEBUG("h=%d", (gobj)->h);                   \
    LOG_DEBUG("x_speed=%d", (gobj)->x_speed);       \
    LOG_DEBUG("y_speed=%d", (gobj)->y_speed);       \
    LOG_DEBUG("health=%d", (gobj)->health);         \
    LOG_DEBUG("spawn_x=%d", (gobj)->x);             \
    LOG_DEBUG("spawn_y=%d", (gobj)->y)

void GameObject_Init(GameObject *gameobject, RECT *bounds, void *prim, const uint16_t spawn_x, const uint16_t spawn_y, const int16_t w, const int16_t h, const int16_t x_speed, const int16_t y_speed, const uint8_t health) {
    gameobject->w = w;
    gameobject->h = h;
    gameobject->prim = prim;
    gameobject->x_speed = x_speed;
    gameobject->y_speed = y_speed;
    gameobject->health = health;
    gameobject->x = spawn_x;
    gameobject->y = spawn_y;
    gameobject->heading = 0;
    gameobject->can_move = 1;
    gameobject->bounds = bounds;
    setRECT(bounds, spawn_x, spawn_y, w, h);
    LOG_GOBJ(DEBUG, gameobject);
}

void GameObject_Tick(GameObject *game_object) {
    game_object->x += game_object->x_speed;
    game_object->y += game_object->y_speed;
    game_object->bounds->x += game_object->x_speed;
    game_object->bounds->y += game_object->y_speed;
}

void GameObject_CameraInit(Camera *cam, GameObject *obj_in_focus) {
    cam->x = cam->y = 0;
    cam->viewport_w = GPU_SCREEN_W;
    cam->viewport_h = GPU_SCREEN_H;
    cam->map_w = GPU_SCREEN_W << 1;
    cam->map_h = GPU_SCREEN_H << 1;
    cam->obj_in_focus = obj_in_focus;
}

void GameObject_CameraTick(Camera *cam) {
    const uint16_t obj_x = cam->obj_in_focus->bounds->x + (cam->obj_in_focus->bounds->w >> 1);
    const uint16_t obj_y = cam->obj_in_focus->bounds->y + (cam->obj_in_focus->bounds->h >> 1);

    // If nothing to focus on then don't do anything
    if (cam->obj_in_focus == NULL) {
        return;
    }

    // Set game object in the middle of the viewport
    int16_t x = obj_x - (cam->viewport_w >> 1);
    int16_t y = obj_y - (cam->viewport_h >> 1);

    // Handle clamping
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x + cam->viewport_w > cam->map_w) {
        x = (cam->map_w - cam->viewport_w);
    }
    if (y + cam->viewport_h > cam->map_h) {
        y = (cam->map_h - cam->viewport_h);
    }
    cam->x = x;
    cam->y = y;
}