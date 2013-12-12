#ifndef font_h
#define font_h

#include <stdlib.h>
#include <wchar.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_helpers.h"

#define MAX_GLYPHS 256
typedef struct font_t font_t;
struct font_t{
    SDL_Surface *glyphs[MAX_GLYPHS];
};

font_t *font_create(const char *image_fn);
void font_delete(font_t *font);

void font_draw_all_glyphs(font_t *font, int x, int y, SDL_Surface *target);
void font_draw_string(font_t *font, const wchar_t *string, int32_t x, int32_t y, SDL_Surface *target);

int32_t font_get_height(font_t *font);
#endif
