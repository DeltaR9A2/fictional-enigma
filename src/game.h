#ifndef game_h
#define game_h

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <tgmath.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>

typedef struct game_t game_t;

#include "core.h"
#include "rect.h"

#include "font.h"
#include "anim.h"
#include "sprite.h"
#include "camera.h"
#include "player.h"

#include "controller.h"

#include "loader.h"

#include "fset_wmap.h"
#include "anim_wmap.h"

#include "rect_list.h"
#include "body_list.h"

struct game_t{
    core_t *core;
    uint32_t step;

    controller_t controller;
    
    rect_t *mouse;
    rect_t *bounds;
    
    camera_t *camera;    
    player_t *player;

    fset_wmap_t *fsets;
    anim_wmap_t *anims;
    
    body_list_t *phys_body_list;
    rect_list_t *terr_rect_list;
    rect_list_t *plat_rect_list;
    
    font_t *fonts;
};

game_t *game_create(core_t *core);
void game_delete(game_t *game);

void game_fast_frame(game_t *game);
void game_full_frame(game_t *game);

#endif
