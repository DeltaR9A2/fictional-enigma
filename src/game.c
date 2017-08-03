#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#include "game.h"
#include "rect.h"

#include "lua_bindings.h"

const uint32_t GAME_MODE_MENU = 0;
const uint32_t GAME_MODE_PLAY = 1;
const uint32_t GAME_MODE_DIALOGUE = 2;

const uint32_t GAME_MESSAGE_LEN = 128;
const uint32_t GAME_DIALOGUE_LEN = 128;

void game_create_data_structures(game_t *game);
void game_delete_data_structures(game_t *game);

void game_set_message(game_t *game, const char *text){
	game->message_timeout = 240;
	sprintf(game->message, "%s", text);

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
void game_set_dialogue(game_t *game, const char *portrait, const char *message){
	dialogue_timer = 0;

	game->dialogue_portrait = load_image(portrait);
	sprintf(game->dialogue_content, message);
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

void game_update_items(game_t *game){
	for(item_node_t *iter = game->items->head; iter; iter = iter->next){
		if(iter->data->flags & ITEM_ALIVE){
			item_update(iter->data);
			do_physics_to_it(iter->data->body, game->terrain_rects, game->platform_rects);
			if(rect_overlap(iter->data->body->rect, game->player->body->rect)){
				game->hud->counter->count += 1;
				iter->data->flags &= !ITEM_ALIVE;
			}
		}
	}
}

game_t *game_create(core_t *core){
  printf("Begin game_create.\n");
  fflush(stdout);
  
	game_t *game = malloc(sizeof(game_t));

	game->core = core;
	game->step = 0;
	game->mode = GAME_MODE_PLAY;

	game_create_data_structures(game);

	game->font = font_create("font_nokia.png");
	game->debug_font = font_create("font_nokia.png");

	game->menu = menu_create_main_menu(game);
	game->hud = hud_create(game);
	
	camera_init(game->camera, 640, 360);

	game->message = calloc(GAME_MESSAGE_LEN, sizeof(char));
	game->message_surface = create_surface(640-16, 6+font_get_height(game->font));
	game->message_timeout = 0;

	game->dialogue_content = calloc(GAME_DIALOGUE_LEN, sizeof(char));
	game->dialogue_surface = create_surface(640-256, 100);
	game->dialogue_portrait = NULL;

	game_load_map(game, "map_default.png", "map_default_image.png");	
	game->player->body->rect->x = (128 - (game->player->body->rect->w/2));
	game->player->body->rect->y = (128 - (game->player->body->rect->h/2));
  printf("Creating LUA state.\n");
	game->LUA = lua_create();
	lua_set_game(game);
	
	printf("Loading LUA scripts... ");
	luaL_loadfile(game->LUA, "init.lua");
	printf("OK\n");
	
	printf("[>>> Begin LUA Execution <<<]\n");
	
	// Turns out an unprotected LUA call is better than protected if all you
	// want is a crash with file and line number.
	lua_call(game->LUA, 0, 0);

	printf("[>>> End LUA Execution <<<]\n");


	player_update(game->player, game);
	
	game_update_targets(game);

	return game;
}

void game_delete(game_t *game){
	free(game->message);

	lua_delete();

	menu_delete(game->menu);	
	font_delete(game->font);

	game_delete_data_structures(game);

	free(game);
}

void game_reset_map(game_t *game){
	item_list_delete(game->items);
	target_dict_delete(game->targets);
	event_dict_delete(game->events);
	rect_list_delete(game->terrain_rects);
 	rect_list_delete(game->platform_rects);
	
	game->platform_rects = rect_list_create();
	game->terrain_rects = rect_list_create();
	game->events = event_dict_create();
	game->targets = target_dict_create();
	game->items = item_list_create();
}

void game_load_map(game_t *game, const char *map_fn, const char *image_fn){
	game_reset_map(game);

	SDL_Surface *map_data = load_image(map_fn);

	cmap_t *terrain_cmap = cmap_create();
	cmap_init(terrain_cmap, 0, 0, map_data->w, map_data->h);

	cmap_t *platform_cmap = cmap_create();
	cmap_init(platform_cmap, 0, 0, map_data->w, map_data->h);

	for(int i=0; i < map_data->w * map_data->h; i++){
		uint32_t pixel = ((Uint32 *)map_data->pixels)[i];

		if(pixel == 0x333366FF){
			terrain_cmap->data[i] = 1;
			platform_cmap->data[i] = 0;
		}else if(pixel == 0x9999DDFF){
			terrain_cmap->data[i] = 0;
			platform_cmap->data[i] = 1;
		}else{
			terrain_cmap->data[i] = 0;
			platform_cmap->data[i] = 0;
		}
	}

	cmap_add_to_rect_list(terrain_cmap, game->terrain_rects);
	cmap_delete(terrain_cmap);

	cmap_add_to_rect_list(platform_cmap, game->platform_rects);
	cmap_delete(platform_cmap);

	rect_init(game->camera->bounds, 0, 0, map_data->w * 8, map_data->h * 8);

	game->map_image = load_image(image_fn);
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
		game_update_items(game);

		if(controller_just_pressed(game->controller, BTN_A)){
			if(game->active_target != NULL){
				target_activate(game->active_target, game);
			}
		}
		if(controller_just_pressed(game->controller, BTN_START)){
			game->mode = GAME_MODE_MENU;
			camera_set_fade(game->camera, 0x000000CC);
		}

	}else if(game->mode == GAME_MODE_DIALOGUE){
		if(controller_just_pressed(game->controller, BTN_A) ||
			controller_just_pressed(game->controller, BTN_B)){
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

void game_draw_hud(game_t *game){
	counter_draw(game->hud->counter, game->core->screen); 
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
	}else{
		game_draw_hud(game);
	}

	if(game->message_timeout > 0){
		game->message_timeout -= 1;
		draw_rect.x = 8;
		draw_rect.y = 360 - (8+game->message_surface->h);

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

	game->events = event_dict_create();
	game->targets = target_dict_create();
	game->items = item_list_create();
}

void game_delete_data_structures(game_t *game){
	item_list_delete(game->items);
	target_dict_delete(game->targets);
	event_dict_delete(game->events);

	rect_list_delete(game->platform_rects);
	rect_list_delete(game->terrain_rects);
	anim_dict_delete(game->anims);
	fset_dict_delete(game->fsets);

	player_delete(game->player);
	camera_delete(game->camera);
	mixer_delete(game->mixer);
	controller_delete(game->controller);
}

