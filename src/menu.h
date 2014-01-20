#ifndef MENU_H
#define MENU_H

typedef struct option_t option_t;
typedef struct menu_t menu_t;

#include <wchar.h>

#include "game.h"

extern const uint32_t OPTION_LABEL_LEN;

struct option_t{
	wchar_t *label;
 	void (*action)(menu_t*);
};

option_t *option_create(wchar_t *label, void (*action)(menu_t*));
void option_delete(option_t *option);
void option_activate(option_t *option, menu_t *menu);


extern const uint32_t MENU_MAX_OPTIONS;

struct menu_t{
	game_t *game;
	option_t **options;
	uint8_t num_options;
	uint8_t selection;
};

menu_t *menu_create(game_t *game);
menu_t *menu_create_main_menu(game_t *game);

void menu_delete(menu_t *menu);

void menu_add_option(menu_t *menu, wchar_t *label, void (*action)(menu_t*));

void menu_up(menu_t *menu);
void menu_down(menu_t *menu);
void menu_activate(menu_t *menu);

void menu_draw(menu_t *menu, SDL_Surface *surface);

void menu_exit(menu_t *menu);
void menu_new_game(menu_t *menu);
void menu_load_game(menu_t *menu);
void menu_options(menu_t *menu);

#endif