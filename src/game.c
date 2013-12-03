#include "game.h"

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;
SDL_Rect arect;

#include "rect.h"
#include "body.h"

#include "physics.h"
#include "sprite.h"
#include "loader.h"

const uint32_t DIR_X = 0;
const uint32_t DIR_R = 1;
const uint32_t DIR_L = 2;

typedef struct player_t player_t;
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

player_t *player_create(void){
    player_t *player = malloc(sizeof(player_t));
    
    player->fall_speed = 7.0;
    player->fall_accel = 0.3;
    
    player->ground_speed = 3.50;
    player->ground_accel = 0.25;
    player->ground_decel = 0.15;
    
    player->jump_force = -6.5;
    player->jump_brake = -2.0;
    
    player->body = body_create();
    player->sprite = sprite_create();
    
    player->face_dir = DIR_R;
    player->ctrl_dir = DIR_X;
    player->move_dir = DIR_X;
    
    return player;
}

void player_delete(player_t *player){
    sprite_delete(player->sprite);
    body_delete(player->body);
    free(player);
}

player_t *player;

//self.dash_vel = 8
//self.dash_timer = 0
//self.air_dash = False

/*
def cmap_to_rects(cmap, map_w, map_h):
    def mark(rect):
        for coord in rect.internal_coords():
            cmap[coord] = 2

    def validate(rect):
        for coord in rect.internal_coords():
            if cmap.get(coord, 0) == 0:
                return False
        return True

    map_rect = ScRect(0, 0, map_w, map_h)

    rects = []
    for coord in map_rect.internal_coords():
        x, y = coord

        if cmap.get(coord, 0) == 1:
            current_rect = ScRect(x, y, 1, 1)

            while validate(current_rect):
                current_rect.w += 1
            current_rect.w -= 1

            while validate(current_rect):
                current_rect.h += 1
            current_rect.h -= 1

            mark(current_rect)

            rects.append(current_rect)

    return rects
*/

void draw_terrain_rects(game_t *game){
    SDL_Rect fill_rect;

    rect_node_t *iter = game->terr_rect_list->head;
    while(iter != NULL){
        rect_copy_to_sdl(iter->data, &fill_rect);
        SDL_FillRect(game->core->screen, &fill_rect, 0x333366FF);
        iter = iter->next;
    }
}

void draw_platform_rects(game_t *game){
    SDL_Rect fill_rect;

    rect_node_t *iter = game->plat_rect_list->head;
    while(iter != NULL){
        rect_copy_to_sdl(iter->data, &fill_rect);
        SDL_FillRect(game->core->screen, &fill_rect, 0x7777AAFF);
        iter = iter->next;
    }
}

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    game->fonts = font_create("font_8bit_operator_black.png");
    
    game->fsets = fset_wmap_create();
    game->anims = anim_wmap_create();
    game->terr_rect_list = rect_list_create();
    game->plat_rect_list = rect_list_create();

    load_framesets(game);
    load_animations(game);
    load_terrain_rects(game);
    load_platform_rects(game);
    
    game->phys_body_list = body_list_create();
    
    player = player_create();
    
    player->body->rect->x = 64;
    player->body->rect->y = 64;
    player->body->rect->w = 28;
    player->body->rect->h = 38;

    sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));

    controller_reset(&game->controller);
    
    return game;
}

void game_delete(game_t *game){
    player_delete(player);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    font_delete(game->fonts);
    
    free(game);
}

void player_update_controls(player_t *player, game_t *game){
    player->body->flags &= ~PLAT_DROP;

    if(player->body->vy < player->fall_speed){
        player->body->vy = fmin(player->fall_speed, player->body->vy + player->fall_accel);
    }

    if(controller_pressed(&game->controller, BTN_D | BTN_A)){
        player->body->flags |= PLAT_DROP;
    }
    
    if(controller_just_pressed(&game->controller, BTN_A)){
        if(player->body->flags & BLOCKED_D && controller_released(&game->controller, BTN_D)){
            player->body->vy = player->jump_force;
        }
    }else if(controller_just_released(&game->controller, BTN_A)){
        if(player->body->vy < player->jump_brake){
            player->body->vy = player->jump_brake;
        }
    }
    
    if(controller_pressed(&game->controller, BTN_R)){
        player->face_dir = DIR_R;
        player->ctrl_dir = DIR_R;
        if(player->body->vx < 0){
            player->body->vx += player->ground_accel;
        }else if(player->body->vx < player->ground_speed){
            player->body->vx = fmin(player->ground_speed, player->body->vx + player->ground_accel);
        }
    }else if(controller_pressed(&game->controller, BTN_L)){
        player->face_dir = DIR_L;
        player->ctrl_dir = DIR_L;
        if(player->body->vx > 0){
            player->body->vx -= player->ground_accel;
        }else if(player->body->vx > -player->ground_speed){
            player->body->vx = fmax(-player->ground_speed, player->body->vx - player->ground_accel);
        }
    }else{
        player->ctrl_dir = DIR_X;
        if(player->body->vx > 0.0){
            player->body->vx = fmax(0.0, player->body->vx - player->ground_decel);
        }else if(player->body->vx < 0.0){
            player->body->vx = fmin(0.0, player->body->vx + player->ground_decel);
        }
    }
    
    if(player->body->vx > 0 && !(player->body->flags & BLOCKED_R)){
        player->move_dir = DIR_R;
    }else if(player->body->vx < 0 && !(player->body->flags & BLOCKED_L)){
        player->move_dir = DIR_L;
    }else{
        player->move_dir = DIR_X;
    }
}

void player_update_animation(player_t *player, game_t *game){
    player->sprite->step += 1;

    if(player->body->flags & BLOCKED_D){
        if(player->move_dir == DIR_X){
            if(player->face_dir == DIR_R){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));
            }else if(player->face_dir == DIR_L){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_l"));
            }
        }else if(player->move_dir == DIR_R){
            if(player->ctrl_dir == DIR_R){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_move_r"));
            }else{
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_skid_r"));
            }
        }else if(player->move_dir == DIR_L){
            if(player->ctrl_dir == DIR_L){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_move_l"));
            }else{
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_skid_l"));
            }
        }
    }else{
        if(player->face_dir == DIR_R){
            if(player->body->vy < -1.0){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_jump_r"));
            }else if(player->body->vy > 1.0){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_hang_r"));
            }else{
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_fall_r"));
            }
        }else if(player->face_dir == DIR_L){
            if(player->body->vy < -1.0){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_jump_l"));
            }else if(player->body->vy > 1.0){
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_hang_l"));
            }else{
                sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_fall_l"));
            }
        }
    }
}

void player_update(player_t *player, game_t *game){
    player_update_controls(player, game);
    player_update_animation(player, game);
    rect_move_to(player->sprite->rect, player->body->rect);
    do_physics_to_it(player->body, game->terr_rect_list, game->plat_rect_list);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    player_update(player, game);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xDDDDDDFF);
    draw_terrain_rects(game);
    draw_platform_rects(game);

    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(player->body->rect));
    font_draw_string(game->fonts, debug_message, 24, 20, game->core->screen);
    
    rect_copy_to_sdl(player->sprite->rect, &arect);
    if(sdl_rect_overlap(&arect, &game->core->active_rect)){
        anim_draw(player->sprite->anim, player->sprite->step, game->core->screen, &arect);
    }
}

