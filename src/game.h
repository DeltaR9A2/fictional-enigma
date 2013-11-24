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
#include "anim.h"
#include "controller.h"

#include "fset_wmap.h"
#include "anim_wmap.h"

typedef struct game_t game_t;
struct game_t{
    core_t *core;
    uint32_t step;

    controller_t controller;

    fset_wmap_t *fsets;
    anim_wmap_t *anims;
    
    font_t *fonts;
};

game_t *game_create(core_t *core);
void game_delete(game_t *game);

void game_fast_frame(game_t *game);
void game_full_frame(game_t *game);

#endif
