#include "game.h"

typedef struct anim_t anim_t;
struct anim_t{
    uint32_t frame_count;
    SDL_Surface *frames;
};

void game_init(game_t *game, core_t *core){
    game->core = core;
    game->frame = 0;
    game->font = font_create("font_8bit_operator_black.png");
}

void game_quit(game_t *game){
    font_destroy(game->font);
}

void game_fast_frame(game_t *game){
    game->frame += 1;
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    font_draw_string(game->font, L"I am not a robot.", 0, 0, game->core->screen);
}

