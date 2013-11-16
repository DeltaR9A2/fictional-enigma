#ifndef frameset_h
#define frameset_h

#include "sdl_helpers.h"

typedef struct frameset_t frameset_t;
struct frameset_t{
    int len;
    SDL_Surface **frames;
};

frameset_t *frameset_create(const char *fn, int cols, int rows);

void frameset_delete(frameset_t *frameset);

#endif
