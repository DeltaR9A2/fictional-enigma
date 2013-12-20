#ifndef player_h
#define player_h

#include <math.h>

typedef struct player_t player_t;

#include "game.h"
#include "body.h"
#include "sprite.h"
#include "physics.h"

//self.dash_vel = 8
//self.dash_timer = 0
//self.air_dash = False

struct player_t{
    body_t *body;
    sprite_t *sprite;
    uint32_t flashing;

    rect_t *weapon;
    uint32_t weapon_life;
    uint32_t weapon_delay;

    ///// Physics Vars
    double fall_speed;
    double fall_accel;
    
    double ground_speed;
    double ground_accel;
    double ground_decel;
    
    double jump_force;
    double jump_brake;
    
    uint32_t face_dir;
    uint32_t ctrl_dir;
    uint32_t move_dir;
    /////
};

player_t *player_create(void);
void player_delete(player_t *player);

void player_update(player_t *player, game_t *game);
void player_update_controls(player_t *player, game_t *game);
void player_update_animation(player_t *player, game_t *game);

#endif
