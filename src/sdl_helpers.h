#ifndef sdl_helpers_h
#define sdl_helpers_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *create_surface(int32_t w, int32_t h);
SDL_Texture *create_texture(SDL_Renderer *render, int32_t w, int32_t h);
SDL_Texture *create_streaming_texture(SDL_Renderer *render, int32_t w, int32_t h);

#endif
