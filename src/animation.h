#ifndef anim_h
#define anim_h

#include "frameset.h"

typedef struct anim_t anim_t;
struct anim_t{
    int len, fps;
    SDL_Surface **frames;
};

anim_t *anim_create(int len, int fps);
void anim_delete(anim_t *anim);
void anim_add_frame(anim_t *anim, frameset_t *frameset, int frame_index);
void anim_set_frames(anim_t *anim, frameset_t *frameset, int start_index);
void anim_draw(anim_t *anim, int step, SDL_Surface *target, SDL_Rect *dest);

#endif
