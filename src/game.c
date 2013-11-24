#include "game.h"

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;
SDL_Rect arect;

#include "rect.h"
#include "body.h"


void do_physics_to_it(body_t *body, rect_list_t *terr_rects, rect_list_t *plat_rects){
    rect_t *start = rect_create();
    rect_match_to(start, body->rect);
    
    rect_node_t *iter;
    
    body->flags &= ~BLOCKED_MASK;
    
    body->rect->x += body->vx;
    iter = terr_rects->head;
    while(iter != NULL){
        if(rect_overlap(body->rect, iter->data)){
            if(body->vx > 0 && rect_get_r_edge(body->rect) >= rect_get_l_edge(iter->data)){
                body->vx = 0;
                rect_set_r_edge(body->rect, rect_get_l_edge(iter->data));
                body->flags |= BLOCKED_R;
            }else if(body->vx < 0 && rect_get_l_edge(body->rect) <= rect_get_r_edge(iter->data)){
                body->vx = 0;
                rect_set_l_edge(body->rect, rect_get_r_edge(iter->data));
                body->flags |= BLOCKED_L;
            }
            break;
        }
        iter = iter->next;
    }

    body->rect->y += body->vy;
    iter = terr_rects->head;
    while(iter != NULL){
        if(rect_overlap(body->rect, iter->data)){
            if(body->vy > 0 && rect_get_b_edge(body->rect) >= rect_get_t_edge(iter->data)){
                body->vy = 0;
                rect_set_b_edge(body->rect, rect_get_t_edge(iter->data));
                body->flags |= BLOCKED_D;
            }else if(body->vy < 0 && rect_get_t_edge(body->rect) <= rect_get_b_edge(iter->data)){
                body->vy = 0;
                rect_set_t_edge(body->rect, rect_get_b_edge(iter->data));
                body->flags |= BLOCKED_U;
            }
            break;
        }
        iter = iter->next;
    }
    
    if(body->vy > 0 && !(body->flags & PLAT_DROP)){
        iter = plat_rects->head;
        while(iter != NULL){
            if(rect_overlap(body->rect, iter->data)){
                if(rect_get_b_edge(start) <= rect_get_t_edge(iter->data)){
                    body->vy = 0;
                    rect_set_b_edge(body->rect, rect_get_t_edge(iter->data));
                    body->flags |= BLOCKED_D;
                }
                break;
            }
            iter = iter->next;
        }
    }
    
    rect_delete(start);
}

typedef struct sprite_t sprite_t;
struct sprite_t{
    rect_t *rect;
    anim_t *anim;
    int step;
};

sprite_t *sprite_create(){
    sprite_t *sprite = malloc(sizeof(sprite_t));
    sprite->rect = rect_create();
    return sprite;
}

void sprite_delete(sprite_t *sprite){
    rect_delete(sprite->rect);
    free(sprite);
}

void sprite_set_anim(sprite_t *sprite, anim_t *anim){
    if(sprite->anim != anim){
        sprite->anim = anim;
        sprite->step = 0;
    }
}

rect_t *terrain;
rect_t *platform;

body_t *body;
sprite_t *sprite;

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    game->fonts = font_create("font_8bit_operator_black.png");
    
    game->fsets = fset_wmap_create();
    game->anims = anim_wmap_create();
    
    fset_one = fset_wmap_get(game->fsets, L"player_anarchy_female");
    fset_init(fset_one, "player_anarchy_female.png", 8, 4);
    
    anim_one = anim_wmap_get(game->anims, L"ana_f_idle");
    anim_init(anim_one, fset_one, 0, 6,  8);

    anim_two = anim_wmap_get(game->anims, L"ana_f_run");
    anim_init(anim_two, fset_one, 8, 8, 10);
    
    game->terr_rect_list = rect_list_create();
    game->plat_rect_list = rect_list_create();
    
    terrain = rect_list_get(game->terr_rect_list);
    terrain->x = 0;
    terrain->y = 360;
    terrain->w = 640;
    terrain->h = 8;
    
    platform = rect_list_get(game->plat_rect_list);
    platform->x = 0;
    platform->y = 320;
    platform->w = 320;
    platform->h = 8;
    
    game->phys_body_list = body_list_create();
    body = body_list_get(game->phys_body_list);
    body->rect->x = 64;
    body->rect->y = 64;
    body->rect->w = 64;
    body->rect->h = 64;

    sprite = sprite_create();
    sprite->rect->x = 32;
    sprite->rect->y = 32;
    sprite->rect->w = 64;
    sprite->rect->h = 64;
    sprite->anim = anim_one;
    
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
    
    if(body->vy < 4.0){
        body->vy += 0.1;
    }

    if(body->flags & BLOCKED_D && controller_just_pressed(&game->controller, BTN_A)){
        body->vy = -4.0;
    }
    
    if(controller_pressed(&game->controller, BTN_D)){
        body->flags |= PLAT_DROP;
    }else{
        body->flags &= ~PLAT_DROP;
    }
    
    if(controller_pressed(&game->controller, BTN_R)){
        body->vx = 2.5;
        sprite_set_anim(sprite, anim_two);
    }else if(controller_pressed(&game->controller, BTN_L)){
        body->vx = -2.5;
        sprite_set_anim(sprite, anim_two);
    }else{
        body->vx = 0.0;
        sprite_set_anim(sprite, anim_one);
    }
    
    do_physics_to_it(body, game->terr_rect_list, game->plat_rect_list);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(body->rect));
    font_draw_string(game->fonts, debug_message, 8, 4, game->core->screen);
    
    rect_move_to(sprite->rect, body->rect);
    rect_copy_to_sdl(sprite->rect, &arect);
    if(sdl_rect_overlap(&arect, &game->core->active_rect)){
        anim_draw(sprite->anim, sprite->step, game->core->screen, &arect);
    }
}

