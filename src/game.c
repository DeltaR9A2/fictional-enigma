#include "game.h"

frameset_t *frameset;

anim_t *animations[256];

SDL_Rect arect;

int current_anim = 0;

wchar_t debug_message[128];

void game_init(game_t *game, core_t *core){
    game->core = core;
    game->step = 0;
    game->font = font_create("font_8bit_operator_black.png");
    
    for(int i=0; i<256; i++){
        animations[i] = NULL;
    }
    
    frameset = frameset_create("player_anarchy_female.png", 8, 4);

    animations[0] = anim_create(6, 8);
    anim_set_frames(animations[0], frameset, 0);

    animations[1] = anim_create(8, 10);
    anim_set_frames(animations[1], frameset, 8);

    arect.x = 100;
    arect.y = 100;
}

void game_quit(game_t *game){
    for(int i=0; i<256; i++){
        if(animations[i] != NULL){
            anim_delete(animations[i]);
        }
    }
    frameset_delete(frameset);
    font_delete(game->font);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    if(controller_pressed(&game->core->controller, BTN_R)){
        current_anim = 1;
        arect.x += 2;
    }else if(controller_pressed(&game->core->controller, BTN_L)){
        current_anim = 1;
        arect.x -= 2;
    }else{
        current_anim = 0;
    }
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    swprintf(debug_message, 100, L"Window Size: %ix%i  Active Size: %ix%i", game->core->win_cw, game->core->win_ch, game->core->active_rect.w, game->core->active_rect.h);
    font_draw_string(game->font, debug_message, 8, 4, game->core->screen);
    anim_draw(animations[current_anim], game->step, game->core->screen, &arect);
}

