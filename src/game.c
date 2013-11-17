#include "game.h"

frameset_t *frameset_anarchy;
frameset_t *frameset_empress;

anim_t *anim_anarchy;
anim_t *anim_empress;

SDL_Rect anim_rect_anarchy;
SDL_Rect anim_rect_empress;

wchar_t debug_message[128];

void game_init(game_t *game, core_t *core){
    game->core = core;
    game->step = 0;
    game->font = font_create("font_8bit_operator_black.png");
    
    frameset_anarchy = frameset_create("player_anarchy_female.png", 8, 4);
    frameset_empress = frameset_create("player_empress.png", 8, 4);

    anim_anarchy = anim_create(8, 10);
    anim_set_frames(anim_anarchy, frameset_anarchy, 0);

    anim_empress = anim_create(8, 10);
    anim_set_frames(anim_empress, frameset_empress, 0);

    anim_rect_anarchy.x = 100;
    anim_rect_anarchy.y = 100;

    anim_rect_empress.x = 164;
    anim_rect_empress.y = 100;
}

void game_quit(game_t *game){
    anim_delete(anim_anarchy);    
    anim_delete(anim_empress);    
    frameset_delete(frameset_anarchy);
    frameset_delete(frameset_empress);
    font_delete(game->font);
}

void game_fast_frame(game_t *game){
    game->step += 1;
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    swprintf(debug_message, 100, L"Window Size: %ix%i  Active Size: %ix%i", game->core->win_cw, game->core->win_ch, game->core->active_rect.w, game->core->active_rect.h);
    font_draw_string(game->font, debug_message, 8, 4, game->core->screen);
    anim_draw(anim_anarchy, game->step, game->core->screen, &anim_rect_anarchy);
    anim_draw(anim_empress, game->step, game->core->screen, &anim_rect_empress);
}

