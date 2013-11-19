#include "game.h"

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;
SDL_Rect arect;

#include "rect.h"

typedef struct body_t body_t;
struct body_t{
    rect_t *rect;
    double vx, vy;
};

body_t *body_create(void){
    body_t *body = malloc(sizeof(body_t));
    body->rect = rect_create();
    body->vx = 0;
    body->vy = 0;
    return body;
}

void body_delete(body_t *body){
    rect_delete(body->rect);
    free(body);
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

body_t *body;
sprite_t *sprite;

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    game->fonts = font_create("font_8bit_operator_black.png");
    
    game->fsets = fset_create("player_anarchy_female.png", L"player_anarchy_female", 8, 4);

    game->anims = anim_create(L"ana_f_idle", 6, 8);
    anim_list_add(game->anims, anim_create(L"ana_f_run", 8, 10));
    
    fset_one = fset_list_get(game->fsets, L"player_anarchy_female");
    anim_one = anim_list_get(game->anims, L"ana_f_idle");
    anim_two = anim_list_get(game->anims, L"ana_f_run");
    
    anim_set_frames(anim_one, fset_one, 0);
    anim_set_frames(anim_two, fset_one, 8);

    body = body_create();
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
    anim_list_delete(game->anims);
    fset_list_delete(game->fsets);
    font_delete(game->fonts);
    
    free(game);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    sprite->step += 1;
    
    if(rect_get_b_edge(body->rect) < 360){
        if(body->vy < 4.0){
            body->vy += 0.1;
        }
    }else{
        if(controller_pressed(&game->controller, BTN_A)){
            body->vy = -4.0;
        }else{
            body->vy = 0.0;
        }
    }
    
    if(controller_pressed(&game->controller, BTN_R)){
        sprite_set_anim(sprite, anim_two);
        
        body->rect->x += 2.5;
    }else if(controller_pressed(&game->controller, BTN_L)){
        sprite_set_anim(sprite, anim_two);
        
        body->rect->x -= 2.5;
    }else{
        sprite_set_anim(sprite, anim_one);
    }
    
    body->rect->x += body->vx;
    body->rect->y += body->vy;
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    swprintf(debug_message, 100, L"Window Size: %ix%i  Active Size: %ix%i", game->core->win_cw, game->core->win_ch, game->core->active_rect.w, game->core->active_rect.h);
    font_draw_string(game->fonts, debug_message, 8, 4, game->core->screen);
    
    rect_move_to(sprite->rect, body->rect);
    rect_copy_to_sdl(sprite->rect, &arect);
    if(sdl_rect_overlap(&arect, &game->core->active_rect)){
        anim_draw(sprite->anim, sprite->step, game->core->screen, &arect);
    }
}

