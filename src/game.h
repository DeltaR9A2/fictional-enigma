#ifndef game_h
#define game_h

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>

#include "core.h"
#include "font.h"

#include "frameset.h"
#include "anim.h"

typedef struct game_t game_t;
struct game_t{
    core_t *core;
    font_t *font;
    uint32_t step;
};

game_t *game_create(core_t *core);
void game_delete(game_t *game);

void game_fast_frame(game_t *game);
void game_full_frame(game_t *game);

#endif
