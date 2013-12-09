#ifndef camera_h
#define camera_h

typedef struct camera_t camera_t;

#include "rect.h"
#include "game.h"
#include "player.h"

struct camera_t{
    rect_t *view;
    SDL_Surface *buffer;
};

camera_t *camera_create(void);
void camera_init(camera_t *camera, int32_t w, int32_t h);
void camera_delete(camera_t *camera);

void camera_fill_rect(camera_t *camera, rect_t *rect, int32_t color);

void camera_draw_game(camera_t *camera, game_t *game);
void camera_draw_terrain_rects(camera_t *camera, game_t *game);
void camera_draw_platform_rects(camera_t *camera, game_t *game);
void camera_draw_player(camera_t *camera, player_t *player);

#endif
