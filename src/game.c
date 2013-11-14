#include "game.h"

void game_init(game_t *game, core_t *core){
    game->core = core;
    game->frame = 0;
}

void game_fast_frame(game_t *game){
    game->frame += 1;
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
}

