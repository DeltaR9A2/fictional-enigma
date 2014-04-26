#include "loader.h"

#include <wchar.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "cmap.h"

void load_map(game_t *game, char *filename){
	printf("Entering load_map\n");
	SDL_Surface *map_image = load_image(filename);

	cmap_t *terrain_cmap = cmap_create();
	cmap_init(terrain_cmap, 0, 0, 128, 128);

	cmap_t *platform_cmap = cmap_create();
	cmap_init(platform_cmap, 0, 0, 128, 128);

	printf("load_map: Beginning for loop.\n");
	for(int i=0; i < map_image->w * map_image->h; i++){
		uint32_t pixel = ((Uint32 *)map_image->pixels)[i];

		if(pixel == 0x333366FF){
			terrain_cmap->data[i] = 1;
			platform_cmap->data[i] = 0;
		}else if(pixel == 0x9999DDFF){
			terrain_cmap->data[i] = 0;
			platform_cmap->data[i] = 1;
		}else{
			terrain_cmap->data[i] = 0;
			platform_cmap->data[i] = 0;

			if(pixel != 0xFFFFFFFF){
				target_t *target = target_list_get(game->targets);
				target->rect->x = (i % 128) * 8;
				target->rect->y = (i / 128) * 8;
				target->rect->w = 8;
				target->rect->h = 8;
				target->color = pixel;
			}
		}
	}
	printf("load_map: Exiting for loop.\n");

	cmap_add_to_rect_list(terrain_cmap, game->terrain_rects);
	cmap_delete(terrain_cmap);

	cmap_add_to_rect_list(platform_cmap, game->platform_rects);
	cmap_delete(platform_cmap);

	SDL_FreeSurface(map_image);
}

static game_t *GAME;

static int lua_load_map(lua_State *L){
	char *filename = luaL_checkstring(L,1);
	
	load_map(GAME, filename);
	
	return 0;
}

static int lua_add_fset(lua_State *L){
	char *fset_name = luaL_checkstring(L,1);
	char *file_name = luaL_checkstring(L,2);
	int cols = luaL_checkint(L,3);
	int rows = luaL_checkint(L,4);
	bool flip = lua_toboolean(L,5);

	wchar_t real_name[32];
	swprintf(real_name, 32, L"%s", fset_name);

	fset_t *fset = fset_dict_get(GAME->fsets, real_name);
	fset_init(fset, file_name, cols, rows, flip);
	
	return 0;
}

static int lua_add_anim(lua_State *L){
	char *fset_name = luaL_checkstring(L,1);
	char *anim_name = luaL_checkstring(L,2);
	int start = luaL_checkint(L,3);
	int length = luaL_checkint(L,4);
	int rate = luaL_checkint(L,5);
	
	wchar_t w_fset_name[32];
	swprintf(w_fset_name, 32, L"%s", fset_name);

	wchar_t w_anim_name[32];
	swprintf(w_anim_name, 32, L"%s", anim_name);

	fset_t *fset = fset_dict_get(GAME->fsets, w_fset_name);
	anim_t *anim = anim_dict_get(GAME->anims, w_anim_name);

	anim_init(anim, fset, start, length, rate);
	
	return 0;
}

static int lua_configure_target(lua_State *L){
	int color = luaL_checkint(L,1);

	char *anim_name = luaL_checkstring(L,2);
	char *portrait = luaL_checkstring(L,3);
	char *message = luaL_checkstring(L,4);

	wchar_t conversion_buffer[128];

	#ifdef DEBUG
	printf("Configuring %08X %s %s %s\n", color, anim_name, portrait, message);
	#endif

	target_node_t *iter = GAME->targets->head;
	while(iter != NULL){
		if(iter->data->color == color){
			iter->data->sprite = sprite_create();
			
			swprintf(conversion_buffer, 128, L"%hs", anim_name);
			sprite_set_anim(iter->data->sprite, anim_dict_get(GAME->anims, conversion_buffer));
			rect_set_l_edge(iter->data->sprite->rect, rect_get_l_edge(iter->data->rect));
			rect_set_t_edge(iter->data->sprite->rect, rect_get_t_edge(iter->data->rect));
			//rect_move_to(iter->data->sprite->rect, iter->data->rect);
			
			iter->data->portrait = load_image(portrait);
			swprintf(iter->data->message, 128, L"%s", message);
		}
		iter = iter->next;
	}	
	
	return 0;
}

void load_scripts(game_t *game){
	lua_State *LUA = luaL_newstate();
	luaL_openlibs(LUA);

	lua_pushcfunction(LUA, lua_load_map);
	lua_setglobal(LUA, "load_map");

	lua_pushcfunction(LUA, lua_add_fset);
	lua_setglobal(LUA, "add_fset");

	lua_pushcfunction(LUA, lua_add_anim);
	lua_setglobal(LUA, "add_anim");
	
	lua_pushcfunction(LUA, lua_configure_target);
	lua_setglobal(LUA, "configure_target");
	
	luaL_loadfile(LUA, "init.lua");
	lua_pcall(LUA, 0, LUA_MULTRET, 0);
	
	lua_close(LUA);
}

void load_game(game_t *game){
	GAME = game;
	load_scripts(game);
}

