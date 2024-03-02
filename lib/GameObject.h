#ifndef PSX_GAME_OBJECT_H
#define PSX_GAME_OBJECT_H

#include "sys/types.h"
#include "libgte.h"
#include "libgpu.h"

#define GOBJ_TYPE_PLAYER 0x0
#define GOBJ_TYPE_NPC 0x1

#define GOBJ_HEADING_NONE 0x0
#define GOBJ_HEADING_UP 0x1
#define GOBJ_HEADING_DOWN 0x2
#define GOBJ_HEADING_LEFT 0x4
#define GOBJ_HEADING_RIGHT 0x8

typedef struct GameObject {
    void *prim;
    RECT *bounds;
    short old_x, old_y;
    u_short w, h;
    u_char x, y;
    short x_speed, y_speed;
    u_char health: 7;
    u_char can_move: 1;
    u_char heading;
} GameObject;


typedef struct Camera {
    short x, y;
    u_short viewport_w, viewport_h;
    u_short map_w, map_h;
    GameObject *obj_in_focus;
} Camera;

#define GOBJ_SWITCH_DIR(gobj)   \
    (gobj)->x_speed *= -1;      \
    (gobj)->y_speed *= -1

#define GOBJ_SWITCH_X_DIR(gobj) ((gobj)->x_speed *= -1)
#define GOBJ_SWITCH_Y_DIR(gobj) ((gobj)->y_speed *= -1)

#define GOBJ_IS_MOVING(gobj) ((gobj)->heading | GOBJ_HEADING_NONE)

#define GOBJ_IS_HEADING_RIGHT(gobj) ((gobj)->heading & GOBJ_HEADING_RIGHT)
#define GOBJ_IS_HEADING_LEFT(gobj) ((gobj)->heading & GOBJ_HEADING_LEFT)
#define GOBJ_IS_HEADING_UP(gobj) ((gobj)->heading & GOBJ_HEADING_UP)
#define GOBJ_IS_HEADING_DOWN(gobj) ((gobj)->heading & GOBJ_HEADING_DOWN)

#define GOBJ_ANIM_CYCLE_COMPLETE(anim) anim->acc_ticks >= (anim)->ticks_per_frame

#define GOBJ_IS_NOT_MOVING(gobj) !GOBJ_IS_MOVING(gobj)


void gobj_init(GameObject *gobj, RECT *bounds, void *prim, u_short spawn_x, u_short spawn_y, short w, short h, short x_speed, short y_speed, u_char health);
/**
 * Draw the game object
 * @param game_object the game object image to draw
 */
void gobj_draw(GameObject *game_object);

/**
 * Update the game object
 * @param game_object the game object to update
 * @param player how to interact with player
 */
void gobj_tick(GameObject *game_object);

void gobj_camera_init(Camera *cam, GameObject *obj_in_focus);
void gobj_camera_tick(Camera *cam);

#endif // PSX_GAME_OBJECT_H
