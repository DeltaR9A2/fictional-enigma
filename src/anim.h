#ifndef anim_h
#define anim_h

#include <wchar.h>

#include "sdl_helpers.h"

#include "fset.h"

typedef struct anim_t anim_t;
struct anim_t{
    int len, fps;
    SDL_Surface **frames;
};

anim_t *anim_create(void);
void anim_init(anim_t *anim, fset_t *fset, int start, int len, int fps);
void anim_delete(anim_t *anim);

void anim_draw(anim_t *anim, int step, SDL_Surface *target, SDL_Rect *dest);

#endif
