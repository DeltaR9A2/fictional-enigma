#include "game.h"

fset_t *fsets = NULL;
anim_t *anims = NULL;

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;

SDL_Rect arect;

anim_t *current_anim = NULL;

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    game->font = font_create("font_8bit_operator_black.png");
    
    fsets = fset_create("player_anarchy_female.png", L"player_anarchy_female", 8, 4);

    anims = anim_create(L"ana_f_idle", 6, 8);
    anim_list_add(anims, anim_create(L"ana_f_run", 8, 10));
    
    fset_one = fset_list_get(fsets, L"player_anarchy_female");
    anim_one = anim_list_get(anims, L"ana_f_idle");
    anim_two = anim_list_get(anims, L"ana_f_run");
    
    anim_set_frames(anim_one, fset_one, 0);
    anim_set_frames(anim_two, fset_one, 8);

    arect.x = 100;
    arect.y = 100;
    
    return game;
}

void game_delete(game_t *game){
    anim_list_delete(anims);
    fset_list_delete(fsets);
    font_delete(game->font);
    
    free(game);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    if(controller_pressed(&game->core->controller, BTN_R)){
        current_anim = anim_two;
        arect.x += 2;
    }else if(controller_pressed(&game->core->controller, BTN_L)){
        current_anim = anim_two;
        arect.x -= 2;
    }else{
        current_anim = anim_one;
    }
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    swprintf(debug_message, 100, L"Window Size: %ix%i  Active Size: %ix%i", game->core->win_cw, game->core->win_ch, game->core->active_rect.w, game->core->active_rect.h);
    font_draw_string(game->font, debug_message, 8, 4, game->core->screen);
    anim_draw(current_anim, game->step, game->core->screen, &arect);
}

