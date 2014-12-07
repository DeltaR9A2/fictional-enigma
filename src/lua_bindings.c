#include "lua_bindings.h"


static game_t *GAME = NULL;
static lua_State *LUA = NULL;

static void lua_bind_functions();

lua_State *lua_create(){
	if(LUA == NULL){
		LUA = luaL_newstate();
		luaL_openlibs(LUA);

		lua_bind_functions();
	}

	return LUA;
}

void lua_delete(){
	lua_close(LUA);
}

void lua_set_game(game_t *game){
	GAME = game;
}

static int lua_load_map(lua_State *L){
	const char *filename = luaL_checkstring(L,1);

	SDL_Surface *map_image = load_image(filename);

	cmap_t *terrain_cmap = cmap_create();
	cmap_init(terrain_cmap, 0, 0, map_image->w, map_image->h);

	cmap_t *platform_cmap = cmap_create();
	cmap_init(platform_cmap, 0, 0, map_image->w, map_image->h);

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
		}
	}

	cmap_add_to_rect_list(terrain_cmap, GAME->terrain_rects);
	cmap_delete(terrain_cmap);

	cmap_add_to_rect_list(platform_cmap, GAME->platform_rects);
	cmap_delete(platform_cmap);

	rect_init(GAME->camera->bounds, 0, 0, map_image->w * 8, map_image->h * 8);
	
	SDL_FreeSurface(map_image);

	return 0;
}

static int lua_add_fset(lua_State *L){
	const char *fset_name = luaL_checkstring(L,1);
	const char *file_name = luaL_checkstring(L,2);
	int cols = luaL_checkint(L,3);
	int rows = luaL_checkint(L,4);
	bool flip = lua_toboolean(L,5);

	fset_t *fset = fset_dict_get(GAME->fsets, fset_name);
	fset_init(fset, file_name, cols, rows, flip);
	
	return 0;
}

static int lua_add_anim(lua_State *L){
	const char *fset_name = luaL_checkstring(L,1);
	const char *anim_name = luaL_checkstring(L,2);
	int start = luaL_checkint(L,3);
	int length = luaL_checkint(L,4);
	int rate = luaL_checkint(L,5);
	
	#ifdef DEBUG
		printf("Adding Anim %s %s %i %i %i\n", fset_name, anim_name, start, length, rate);
	#endif

	fset_t *fset = fset_dict_get(GAME->fsets, fset_name);
	anim_t *anim = anim_dict_get(GAME->anims, anim_name);

	anim_init(anim, fset, start, length, rate);
	
	return 0;
}

static int lua_add_event(lua_State *L){
	const char *event_name = luaL_checkstring(L,1);
	const char *func_name = luaL_checkstring(L,2);
	const char *config_string = luaL_checkstring(L,3);
	
	#ifdef DEBUG
		printf("Adding Event: %s %s\n", event_name, func_name);
	#endif

	event_t *event = event_dict_get(GAME->events, event_name);

	lua_getglobal(L, func_name);
	event->lua_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	sprintf(event->config, "%s", config_string);

	#ifdef DEBUG
		printf(">> Ref Num: %i\n", event->lua_ref);
	#endif

	return 0;
}

static int lua_add_target(lua_State *L){
	const char *target_name = luaL_checkstring(L, 1);
	int target_x = luaL_checknumber(L,2);
	int target_y = luaL_checknumber(L,3);
	const char *anim_name = luaL_checkstring(L,4);
	const char *event_name = luaL_checkstring(L,5);

	#ifdef DEBUG
		printf("Configuring Target: %s %i %i %s %s\n", target_name, target_x, target_y, anim_name, event_name);
	#endif

	target_t *target = target_dict_get(GAME->targets, target_name);
	target->rect->x = target_x;
	target->rect->y = target_y;
	target->rect->w = 8;
	target->rect->h = 8;

	target->sprite = sprite_create();
	sprite_set_anim(target->sprite, anim_dict_get(GAME->anims, anim_name));
	rect_set_l_edge(target->sprite->rect, rect_get_l_edge(target->rect));
	rect_set_t_edge(target->sprite->rect, rect_get_t_edge(target->rect));

	target->event = event_dict_get(GAME->events, event_name);
	
	return 0;
}

static int lua_simple_dialogue(lua_State *L){
	const char *portrait = luaL_checkstring(L,1);
	const char *message = luaL_checkstring(L,2);

	game_set_dialogue(GAME, portrait, message);
	GAME->mode = GAME_MODE_DIALOGUE;

	return 0;
}

static int lua_simple_message(lua_State *L){
	const char *message = luaL_checkstring(L,1);
	game_set_message(GAME, message);
	
	return 0;
}

static int lua_move_player_to_target(lua_State *L){
	const char *target_name = luaL_checkstring(L, 1);
	
	target_t *target = target_dict_get(GAME->targets, target_name);

	rect_move_to(GAME->player->body->rect, target->rect);

	return 0;
}

typedef struct lua_binding_t{
	int (*function)(lua_State *L);
	char *lua_name;
} lua_binding_t;

static lua_binding_t bindings[] = {
	{lua_load_map, "load_map"},

	{lua_add_fset, "add_fset"},
	{lua_add_anim, "add_anim"},

	{lua_add_event, "add_event"},
	{lua_add_target, "add_target"},
//	{lua_add_trigger, "add_trigger"},
	
	{lua_simple_dialogue, "simple_dialogue"},
	{lua_simple_message,  "simple_message"},

	{lua_move_player_to_target, "move_player_to_target"},

	{NULL, NULL} // Last element marker.
};

static void lua_bind_functions(){
	for(int i=0; bindings[i].function != NULL; i++){
		lua_pushcfunction(LUA, bindings[i].function);
		lua_setglobal(LUA, bindings[i].lua_name);
	}
}

