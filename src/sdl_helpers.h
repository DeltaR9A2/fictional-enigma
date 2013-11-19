#ifndef sdl_helpers_h
#define sdl_helpers_h

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_rotozoom.h>

SDL_Surface *create_surface(int32_t w, int32_t h);
SDL_Surface *convert_surface(SDL_Surface *src);
SDL_Surface *load_image(const char *fn);

SDL_Texture *create_texture(SDL_Renderer *render, int32_t w, int32_t h);
SDL_Texture *create_streaming_texture(SDL_Renderer *render, int32_t w, int32_t h);

bool sdl_rect_overlap(SDL_Rect *a, SDL_Rect *b);

#endif
