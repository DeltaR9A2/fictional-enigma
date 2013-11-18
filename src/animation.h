#ifndef animation_h
#define animation_h

#include <wchar.h>

#include "sdl_helpers.h"

#define NAME_MAX_LEN 32

typedef struct frameset_t frameset_t;
struct frameset_t{
    wchar_t name[NAME_MAX_LEN];
    frameset_t *next;
    
    int len;
    SDL_Surface **frames;
};

frameset_t *frameset_create(const char *fn, const wchar_t *name, int cols, int rows);
void frameset_delete(frameset_t *frameset);

void frameset_list_add(frameset_t *head, frameset_t *frameset);
frameset_t *frameset_list_get(frameset_t *head, const wchar_t *name);
void frameset_list_delete(frameset_t *head);

typedef struct animation_t animation_t;
struct animation_t{
    wchar_t name[NAME_MAX_LEN];
    animation_t *next;
    
    int len, fps;
    SDL_Surface **frames;
};

animation_t *anim_create(const wchar_t *name, int len, int fps);
void anim_delete(animation_t *anim);
void anim_add_frame(animation_t *anim, frameset_t *frameset, int frame_index);
void anim_set_frames(animation_t *anim, frameset_t *frameset, int start_index);
void anim_draw(animation_t *anim, int step, SDL_Surface *target, SDL_Rect *dest);

void animation_list_add(animation_t *head, animation_t *anim);
animation_t *animation_list_get(animation_t *head, const wchar_t *name);
void animation_list_delete(animation_t *head);


#endif
