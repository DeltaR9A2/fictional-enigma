#include "menu.h"

const uint32_t OPTION_LABEL_LEN = 32;
const uint32_t MENU_MAX_OPTIONS = 8;

option_t *option_create(wchar_t *label, void (*action)(menu_t*)){
	option_t *option = malloc(sizeof(option_t));
	option->label = malloc(sizeof(wchar_t) * OPTION_LABEL_LEN);
	swprintf(option->label, OPTION_LABEL_LEN, label);
	option->action = action;
	return option;
}

void option_delete(option_t *option){
	free(option->label);
	free(option);
}

void option_activate(option_t *option, menu_t *menu){
	if(option->action != NULL){
		option->action(menu);
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

menu_t *menu_create_main_menu(game_t *game){
	menu_t *menu = menu_create(game);
	
	menu_add_option(menu, L"New Game", &menu_new_game);
	menu_add_option(menu, L"Load Game", &menu_load_game);
	menu_add_option(menu, L"Options", &menu_options);
	menu_add_option(menu, L"Exit", &menu_exit);
	
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

void menu_add_option(menu_t *menu, wchar_t *label, void (*action)(menu_t*)){
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
			menu->options[menu->selection]->action(menu);
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

void menu_exit(menu_t *menu){
	menu->game->core->running = false;
}

void menu_new_game(menu_t *menu){
	menu->game->mode = GAME_MODE_PLAY;
}

void menu_load_game(menu_t *menu){
	game_set_message(menu->game, L"'Load Game' not implemented yet.");
}

void menu_options(menu_t *menu){
	game_set_message(menu->game, L"'Options' not implemented yet.");
}

