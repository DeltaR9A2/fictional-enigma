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
    double fall_speed; // 7.0
    double fall_accel; // 0.3
    
    double ground_speed; // 3.50
    double ground_accel; // 0.25
    double ground_decel; // 0.15
    
    double jump_force; // -6.5
    double jump_brake; // -2.0
    
    body_t *body;
    sprite_t *sprite;

    uint32_t face_dir;
    uint32_t ctrl_dir;
    uint32_t move_dir;
};

player_t *player_create(void);
void player_delete(player_t *player);

void player_update(player_t *player, game_t *game);
void player_update_controls(player_t *player, game_t *game);
void player_update_animation(player_t *player, game_t *game);

#endif
