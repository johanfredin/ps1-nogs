#include "GameObject.h"
#include "Logger.h"
#include "Graphics.h"

void gobj_init(GameObject *gobj, RECT *bounds, void *prim, u_short x, u_short y, short w, short h, short x_speed, short y_speed, u_char health) {
    gobj->w = w;
    gobj->h = h;
    gobj->prim = prim;
    gobj->x_speed = x_speed;
    gobj->y_speed = y_speed;
    gobj->health = health;
    gobj->x = x;
    gobj->y = y;
    gobj->heading = 0;
    gobj->can_move = 1;
    gobj->bounds = bounds;
    setRECT(bounds, x, y, w, h);
    LOGR_LOG_GOBJ(DEBUG, gobj);
}

void gobj_tick(GameObject *game_object) {
    game_object->x += game_object->x_speed;
    game_object->y += game_object->y_speed;
    game_object->bounds->x += game_object->x_speed;
    game_object->bounds->y += game_object->y_speed;
}

void gobj_camera_init(Camera *cam, GameObject *obj_in_focus) {
    cam->x = cam->y = 0;
    cam->viewport_w = GFX_SCREEN_W;
    cam->viewport_h = GFX_SCREEN_H;
    cam->map_w = GFX_SCREEN_W << 1;
    cam->map_h = GFX_SCREEN_H << 1;
    cam->obj_in_focus = obj_in_focus;
}

void gobj_camera_tick(Camera *cam) {
    u_short obj_x = cam->obj_in_focus->bounds->x + (cam->obj_in_focus->bounds->w >> 1);
    u_short obj_y = cam->obj_in_focus->bounds->y + (cam->obj_in_focus->bounds->h >> 1);

    // If nothing to focus on then don't do anything
    if (cam->obj_in_focus == NULL) {
        return;
    }

    // Set game object in the middle of the viewport
    short x = (obj_x - (cam->viewport_w >> 1));
    short y = (obj_y - (cam->viewport_h >> 1));

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