#ifndef game_h
#define game_h

#include <stdlib.h>

#include <SDL2/SDL.h>

#include "core.h"

typedef struct game_t game_t;
struct game_t{
    core_t *core;
    uint32_t frame;
};

void game_init(game_t *game, core_t *core);
void game_fast_frame(game_t *game);
void game_full_frame(game_t *game);

#endif
