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

body_t *body = NULL;
sprite_t *sprite = NULL;

const uint32_t DIR_X = 0;
const uint32_t DIR_R = 1;
const uint32_t DIR_L = 2;

uint32_t player_face_dir = 0;
uint32_t player_push_dir = 0;
uint32_t player_real_dir = 0;

const double PLAYER_FALL_SPEED = 7.0;
const double PLAYER_FALL_ACCEL = 0.3;

const double PLAYER_GROUND_SPEED = 3.5;
const double PLAYER_GROUND_ACCEL = 0.35;
const double PLAYER_GROUND_DECEL = 0.15;

const double PLAYER_JUMP_FORCE = -6.5;
const double PLAYER_JUMP_BRAKE = -2.0;

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
    body = body_list_get(game->phys_body_list);
    body->rect->x = 64;
    body->rect->y = 64;
    body->rect->w = 28;
    body->rect->h = 38;

    sprite = sprite_create();
    sprite->rect->x = 32;
    sprite->rect->y = 32;
    sprite->rect->w = 64;
    sprite->rect->h = 64;
    sprite->anim = anim_wmap_get(game->anims, L"frost_f_idle_r");

    controller_reset(&game->controller);
    
    return game;
}

void game_delete(game_t *game){
    sprite_delete(sprite);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    font_delete(game->fonts);
    
    free(game);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    sprite->step += 1;
    
    body->flags &= ~PLAT_DROP;

    if(body->vy < PLAYER_FALL_SPEED){
        body->vy = fmin(PLAYER_FALL_SPEED, body->vy + PLAYER_FALL_ACCEL);
    }

    if(controller_pressed(&game->controller, BTN_D | BTN_A)){
        body->flags |= PLAT_DROP;
    }
    
    if(controller_just_pressed(&game->controller, BTN_A)){
        if(body->flags & BLOCKED_D && controller_released(&game->controller, BTN_D)){
            body->vy = PLAYER_JUMP_FORCE;
        }
    }else if(controller_just_released(&game->controller, BTN_A)){
        if(body->vy < PLAYER_JUMP_BRAKE){
            body->vy = PLAYER_JUMP_BRAKE;
        }
    }
    
    if(controller_pressed(&game->controller, BTN_R)){
        player_face_dir = DIR_R;
        player_push_dir = DIR_R;
        if(body->vx < 0){
            body->vx += PLAYER_GROUND_ACCEL;
        }else if(body->vx < PLAYER_GROUND_SPEED){
            body->vx = fmin(PLAYER_GROUND_SPEED, body->vx + PLAYER_GROUND_ACCEL);
        }
    }else if(controller_pressed(&game->controller, BTN_L)){
        player_face_dir = DIR_L;
        player_push_dir = DIR_L;
        if(body->vx > 0){
            body->vx -= PLAYER_GROUND_ACCEL;
        }else if(body->vx > -PLAYER_GROUND_SPEED){
            body->vx = fmax(-PLAYER_GROUND_SPEED, body->vx - PLAYER_GROUND_ACCEL);
        }
    }else{
        player_push_dir = DIR_X;
        if(body->vx > 0.0){
            body->vx = fmax(0.0, body->vx - PLAYER_GROUND_DECEL);
        }else if(body->vx < 0.0){
            body->vx = fmin(0.0, body->vx + PLAYER_GROUND_DECEL);
        }
    }
    
    if(body->vx > 0 && !(body->flags & BLOCKED_R)){
        player_real_dir = DIR_R;
    }else if(body->vx < 0 && !(body->flags & BLOCKED_L)){
        player_real_dir = DIR_L;
    }else{
        player_real_dir = DIR_X;
    }
    
    if(body->flags & BLOCKED_D){
        if(player_real_dir == DIR_X){
            if(player_face_dir == DIR_R){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));
            }else if(player_face_dir == DIR_L){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_idle_l"));
            }
        }else if(player_real_dir == DIR_R){
            if(player_push_dir == DIR_R){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_move_r"));
            }else{
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_skid_r"));
            }
        }else if(player_real_dir == DIR_L){
            if(player_push_dir == DIR_L){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_move_l"));
            }else{
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_skid_l"));
            }
        }
    }else{
        if(player_face_dir == DIR_R){
            if(body->vy < -1.0){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_jump_r"));
            }else if(body->vy > 1.0){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_hang_r"));
            }else{
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_fall_r"));
            }
        }else if(player_face_dir == DIR_L){
            if(body->vy < -1.0){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_jump_l"));
            }else if(body->vy > 1.0){
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_hang_l"));
            }else{
                sprite_set_anim(sprite, anim_wmap_get(game->anims, L"frost_f_fall_l"));
            }
        }
    }
        
    do_physics_to_it(body, game->terr_rect_list, game->plat_rect_list);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xDDDDDDFF);
    draw_terrain_rects(game);
    draw_platform_rects(game);

    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(body->rect));
    font_draw_string(game->fonts, debug_message, 24, 20, game->core->screen);
    
    rect_move_to(sprite->rect, body->rect);
    rect_copy_to_sdl(sprite->rect, &arect);
    if(sdl_rect_overlap(&arect, &game->core->active_rect)){
        anim_draw(sprite->anim, sprite->step, game->core->screen, &arect);
    }
}

