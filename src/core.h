#ifndef core_h
#define core_h

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "sdl_helpers.h"
#include "controller.h"

typedef struct core_t core_t;
struct core_t{
    bool running;

    SDL_Window *window;
    int32_t win_vw, win_vh;
    int32_t win_cw, win_ch;
    SDL_Rect active_rect;

    SDL_Renderer *rend;
    SDL_Surface *screen;
    SDL_Texture *screen_texture;
    controller_t controller;
};

void core_init(core_t *core);
void core_window_redraw(core_t *core);
void core_window_resize(core_t *core, int32_t w, int32_t h);

#endif
