#ifndef camera_h
#define camera_h

typedef struct camera_t camera_t;

#include "rect.h"
#include "game.h"
#include "player.h"

struct camera_t{
	rect_t *view;
	rect_t *bounds;
	SDL_Surface *buffer;
	
	#ifdef DEBUG
	SDL_Surface *debug_buffer;
	#endif
};

camera_t *camera_create(void);
void camera_init(camera_t *camera, int32_t w, int32_t h);
void camera_delete(camera_t *camera);

void camera_draw_game(camera_t *camera, game_t *game);

#endif
