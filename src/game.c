#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <tgmath.h>

#include <SDL2/SDL.h>

#include "game.h"
#include "loader.h"
#include "rect.h"

const uint32_t GAME_MODE_MENU = 0;
const uint32_t GAME_MODE_PLAY = 1;

const uint32_t GAME_MESSAGE_LEN = 128;

void game_create_data_structures(game_t *game);
void game_delete_data_structures(game_t *game);

void game_set_message(game_t *game, const wchar_t *text){
	game->message_timeout = 240;
	swprintf(game->message, GAME_MESSAGE_LEN, text);

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

	font_draw_string(game->font, game->message, 8, 3, game->message_surface);
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
    rect_init(game->camera->bounds, -128, -128, 1280, 1280);
    
    load_game(game);
    
    game->message = calloc(GAME_MESSAGE_LEN, sizeof(wchar_t));
    game->message_surface = create_surface(640-16, 6+font_get_height(game->font));
	game->message_timeout = 0;

    return game;
}

void game_delete(game_t *game){
	free(game->message);

	menu_delete(game->menu);	
    font_delete(game->font);
	
	game_delete_data_structures(game);
    
    free(game);
}

void game_check_targets(game_t *game){
    for(target_node_t *iter = game->targets->head; iter; iter = iter->next){
        if(rect_overlap(iter->data->rect, game->player->body->rect)){
            if(controller_just_pressed(game->controller, BTN_X)){
                (*iter->data->action)(iter->data, game);
            }
        }
    }
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
	}
	
	if(game->mode == GAME_MODE_PLAY){
		player_update(game->player, game);
		game_check_targets(game);
	}
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    
    if(game->mode == GAME_MODE_MENU){
		SDL_FillRect(game->core->screen, NULL, 0x000000FF);
		menu_draw(game->menu, game->core->screen);
    }
    
    if(game->mode == GAME_MODE_PLAY){
		rect_move_to(game->camera->view, game->player->body->rect);
		camera_draw_game(game->camera, game);
		SDL_BlitSurface(game->camera->buffer, NULL, game->core->screen, NULL);
	}

	if(game->message_timeout > 0){
		game->message_timeout -= 1;
		SDL_Rect draw_rect;
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
}

void game_delete_data_structures(game_t *game){
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

