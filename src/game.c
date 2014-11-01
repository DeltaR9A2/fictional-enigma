#include <stdlib.h>
#include <string.h>
#include <string.h>
//#include <tgmath.h>

#include <SDL.h>

#include "game.h"
#include "loader.h"
#include "rect.h"

const uint32_t GAME_MODE_MENU = 0;
const uint32_t GAME_MODE_PLAY = 1;
const uint32_t GAME_MODE_DIALOGUE = 2;

const uint32_t GAME_MESSAGE_LEN = 128;
const uint32_t GAME_DIALOGUE_LEN = 128;

void game_create_data_structures(game_t *game);
void game_delete_data_structures(game_t *game);

void game_set_message(game_t *game, const char *text){
	game->message_timeout = 240;
	sprintf(game->message, text);

	SDL_Rect fill_rect;
	fill_rect.x = 0;
	fill_rect.y = 0;
	fill_rect.w = game->message_surface->w;
	fill_rect.h = game->message_surface->h;
	SDL_FillRect(game->message_surface, &fill_rect, 0x666666FF);

	fill_rect.x += 2;
	fill_rect.y += 2;
	fill_rect.w -= 4;
	fill_rect.h -= 4;
	SDL_FillRect(game->message_surface, &fill_rect, 0x333333FF);

	font_draw_string(game->font, game->message, 8, 4, game->message_surface);
}

static uint32_t dialogue_timer = 0;
void game_set_dialogue(game_t *game, SDL_Surface *portrait, const char *text){
	dialogue_timer = 0;
	game->dialogue_portrait = portrait;
	sprintf(game->dialogue_content, text);
}

void game_update_targets(game_t *game){
	target_t *nearest_target = NULL;
	int32_t nearest_distance = 9999;
	int32_t current_distance = 9999;

	for(target_node_t *iter = game->targets->head; iter; iter = iter->next){
		if (iter->data->sprite != NULL){
			iter->data->sprite->step += 1;

			current_distance = (int32_t)rect_range_to(iter->data->sprite->rect, game->player->body->rect);
			if (current_distance < nearest_distance){
				nearest_distance = current_distance;
				nearest_target = iter->data;
			}
		}
	}

	if(nearest_distance <= 32 && nearest_target != NULL){
		game->active_target = nearest_target;
	}else{
		game->active_target = NULL;
	}
}

void game_update_enemies(game_t *game){
	enemy_node_t *iter;
	for(iter = game->enemies->head; iter; iter = iter->next){
		enemy_update(iter->data, game);
	}

	for(iter = game->enemies->head; iter; iter = iter->next){
		if(iter->data->alive){
			if(iter->data->flashing > 0){
				iter->data->flashing -= 1;
			}else{
				if(rect_overlap(iter->data->rect, game->player->weapon)){
					iter->data->flashing = 15;
					iter->data->damage += 25;
					printf("Enemy hit by player.\n");
				}
			}

			if(game->player->flashing == 0){
				if(rect_overlap(iter->data->weapon, game->player->body->rect)){
					game->player->flashing = 60;
					printf("Player hit by enemy.\n");
				}
			}
		}
	}
}

game_t *game_create(core_t *core){
	game_t *game = malloc(sizeof(game_t));

	game->core = core;
	game->step = 0;
	game->mode = GAME_MODE_MENU;

	game_create_data_structures(game);

	game->font = font_create("font_8bit.png");
	game->menu = menu_create_main_menu(game);

	camera_init(game->camera, 640, 360);
	load_game(game);

	game->map_image = load_image("test_map_image.png");

	game->message = calloc(GAME_MESSAGE_LEN, sizeof(char));
	game->message_surface = create_surface(640-16, 6+font_get_height(game->font));
	game->message_timeout = 0;

	game->dialogue_content = calloc(GAME_DIALOGUE_LEN, sizeof(char));
	game->dialogue_surface = create_surface(640-256, 100);
	game->dialogue_portrait = NULL;

	player_update(game->player, game);
	game_update_targets(game);

	enemy_t *debug_enemy = enemy_list_get(game->enemies);

	debug_enemy->rect->w = 16;
	debug_enemy->rect->h = 16;
	debug_enemy->body->rect->w = 16;
	debug_enemy->body->rect->h = 32;
	debug_enemy->body->rect->x = 32;
	debug_enemy->body->rect->y = 32;

	debug_enemy->body->vx = 1;

	game_update_enemies(game);

	return game;
}

void game_delete(game_t *game){
	free(game->message);

	menu_delete(game->menu);	
	font_delete(game->font);

	game_delete_data_structures(game);

	free(game);
}

void game_fast_frame(game_t *game){
	game->step += 1;

	if(game->mode == GAME_MODE_MENU){
		if(controller_just_pressed(game->controller, BTN_U)){
			menu_up(game->menu);
		}
		if(controller_just_pressed(game->controller, BTN_D)){
			menu_down(game->menu);
		}
		if(controller_just_pressed(game->controller, BTN_A)){
			menu_activate(game->menu);
		}
		if(controller_just_pressed(game->controller, BTN_START)){
			menu_activate(game->menu);
		}

	}else if(game->mode == GAME_MODE_PLAY){
		player_update(game->player, game);
		game_update_targets(game);
		game_update_enemies(game);

		if(controller_just_pressed(game->controller, BTN_A)){
			if(game->active_target != NULL){
				(*game->active_target->action)(game->active_target, game);
			}
		}
		if(controller_just_pressed(game->controller, BTN_START)){
			game->mode = GAME_MODE_MENU;
		}

	}else if(game->mode == GAME_MODE_DIALOGUE){
		if(controller_just_pressed(game->controller, BTN_A)){
			game->mode = GAME_MODE_PLAY;
		}
	}
}

void game_draw_dialogue(game_t *game){
	SDL_Rect draw_rect;

	draw_rect.x = 0;
	draw_rect.y = 0;
	SDL_BlitSurface(game->dialogue_portrait, NULL, game->core->screen, &draw_rect);

	SDL_FillRect(game->dialogue_surface, NULL, 0x000000FF);

	if(dialogue_timer < strlen(game->dialogue_content)){	dialogue_timer += 1;	}
	font_draw_string_part(game->font, game->dialogue_content, dialogue_timer, 8, 3, game->dialogue_surface);

	draw_rect.x = game->dialogue_portrait->w;
	draw_rect.y = 380-100;
	SDL_BlitSurface(game->dialogue_surface, NULL, game->core->screen, &draw_rect);
}

void game_full_frame(game_t *game){
	SDL_Rect draw_rect;

	game_fast_frame(game);

	rect_move_to(game->camera->view, game->player->body->rect);
	camera_draw_game(game->camera, game);
	SDL_BlitSurface(game->camera->buffer, NULL, game->core->screen, NULL);

	if(game->mode == GAME_MODE_MENU){
		menu_draw(game->menu, game->core->screen);
	}else if(game->mode == GAME_MODE_DIALOGUE){
		game_draw_dialogue(game);
	}

	if(game->message_timeout > 0){
		game->message_timeout -= 1;
		draw_rect.x = 8;
		draw_rect.y = 8;

		SDL_BlitSurface(game->message_surface, NULL, game->core->screen, &draw_rect);
	}
}

void game_create_data_structures(game_t *game){
	game->controller = controller_create();
	game->mixer = mixer_create();
	game->camera = camera_create();
	game->player = player_create();

	game->fsets = fset_dict_create();
	game->anims = anim_dict_create();

	game->terrain_rects = rect_list_create();
	game->platform_rects = rect_list_create();

	game->targets = target_list_create();
	game->enemies = enemy_list_create();
}

void game_delete_data_structures(game_t *game){
	enemy_list_delete(game->enemies);
	target_list_delete(game->targets);

	rect_list_delete(game->platform_rects);
	rect_list_delete(game->terrain_rects);
	anim_dict_delete(game->anims);
	fset_dict_delete(game->fsets);

	player_delete(game->player);
	camera_delete(game->camera);
	mixer_delete(game->mixer);
	controller_delete(game->controller);
}

