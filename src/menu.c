#include "menu.h"

option_t *option_create(wchar_t *label, void (*action)(game_t*)){
	option_t *option = malloc(sizeof(option_t));
	swprintf(option->label, OPTION_LABEL_LEN, label);
	option->action = action;
	return option;
}

void option_delete(option_t *option){
	free(option);
}

void option_activate(option_t *option, game_t *game){
	if(option->action != NULL){
		option->action(game);
	}
}

menu_t *menu_create(game_t *game){
	menu_t *menu = malloc(sizeof(menu_t));

	menu->game = game;
	menu->options = malloc(sizeof(option_t*) * MENU_MAX_OPTIONS);
	
	for(int i=0; i<MENU_MAX_OPTIONS; i++){
		menu->options[i] = NULL;
	}
	
	menu->selection = 0;
	
	return menu;
}

void menu_delete(menu_t *menu){
	for(int i=0; i<MENU_MAX_OPTIONS; i++){
		if(menu->options[i] != NULL){
			option_delete(menu->options[i]);
		}
	}
	
	free(menu);
}

void menu_add_option(menu_t *menu, wchar_t *label, void (*action)(game_t*)){
	for(int i=0; i<MENU_MAX_OPTIONS; i++){
		if(menu->options[i] == NULL){
			menu->options[i] = option_create(label, action);
			menu->num_options = i+1;
			return;
		}
	}
	
	printf("ERROR: MENU: Could not add option '%ls': Menu full.\n", label);
}

void menu_up(menu_t *menu){
	menu->selection -= 1;
	menu->selection %= menu->num_options;
}

void menu_down(menu_t *menu){
	menu->selection += 1;
	menu->selection %= menu->num_options;
}

void menu_activate(menu_t *menu){
	if(menu->options[menu->selection] != NULL){
		if(menu->options[menu->selection]->action != NULL){
			menu->options[menu->selection]->action(menu->game);
		}else{
			printf("ERROR: MENU: Option '%ls' has NULL action.\n", menu->options[menu->selection]->label);
		}
	}
}

void menu_draw(menu_t *menu, SDL_Surface *surface){
	int x = 64;
	int y = 32;
	int h = font_get_height(menu->game->font);
	
	for(int i=0; i<MENU_MAX_OPTIONS; i++){
		if(menu->options[i] != NULL){
			font_draw_string(menu->game->font, menu->options[i]->label, x, y, surface);
		}
		if(i == menu->selection){
			font_draw_string(menu->game->font, L">", x-16, y, surface);
		}
		y += h;
	}
}
