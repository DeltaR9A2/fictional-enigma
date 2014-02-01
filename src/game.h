#ifndef game_h
#define game_h

#include <stdint.h>

typedef struct game_t game_t;

extern const uint32_t GAME_MODE_MENU;
extern const uint32_t GAME_MODE_PLAY;

extern const uint32_t GAME_MESSAGE_LEN;

#include "core.h"

#include "font.h"
#include "menu.h"
#include "mixer.h"
#include "camera.h"
#include "player.h"
#include "controller.h"

#include "fset_dict.h"
#include "anim_dict.h"
#include "rect_list.h"
#include "enemy_list.h"
#include "target_list.h"

struct game_t{
    core_t *core;
    uint32_t step;
    uint32_t mode;

    font_t *font;

    controller_t *controller;
    
    menu_t *menu;
    
    mixer_t *mixer;

    camera_t *camera;   
    fset_dict_t *fsets;
    anim_dict_t *anims;
    
    player_t *player;
    target_list_t *targets;
    rect_list_t *terrain_rects;
    rect_list_t *platform_rects;
    

	wchar_t *message;
	uint32_t message_timeout;
	SDL_Surface *message_surface;
};

game_t *game_create(core_t *core);
void game_delete(game_t *game);

void game_fast_frame(game_t *game);
void game_full_frame(game_t *game);

void game_set_message(game_t *game, const wchar_t *text);
#endif
