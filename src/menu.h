#ifndef MENU_H
#define MENU_H

typedef struct option_t option_t;
typedef struct menu_t menu_t;

#include <wchar.h>

#include "game.h"

#define OPTION_LABEL_LEN 32
#define MENU_MAX_OPTIONS 8

struct option_t{
	wchar_t label[OPTION_LABEL_LEN];
 	void (*action)(game_t*);
};

option_t *option_create(wchar_t *label, void (*action)(game_t*));
void option_delete(option_t *option);
void option_activate(option_t *option, game_t *game);

struct menu_t{
	game_t *game;
	option_t **options;
	uint8_t num_options;
	uint8_t selection;
};

menu_t *menu_create(game_t *game);
void menu_delete(menu_t *menu);

void menu_add_option(menu_t *menu, wchar_t *label, void (*action)(game_t*));

void menu_up(menu_t *menu);
void menu_down(menu_t *menu);
void menu_activate(menu_t *menu);

void menu_draw(menu_t *menu, SDL_Surface *surface);

#endif
