#ifndef anim_h
#define anim_h

#include <wchar.h>

#include "sdl_helpers.h"

#define NAME_MAX_LEN 32

typedef struct fset_t fset_t;
struct fset_t{
    wchar_t name[NAME_MAX_LEN];
    fset_t *next;
    
    int len;
    SDL_Surface **frames;
};

fset_t *fset_create(const char *fn, const wchar_t *name, int cols, int rows);
void fset_delete(fset_t *frameset);

void fset_list_add(fset_t *head, fset_t *frameset);
fset_t *fset_list_get(fset_t *head, const wchar_t *name);
void fset_list_delete(fset_t *head);

typedef struct anim_t anim_t;
struct anim_t{
    wchar_t name[NAME_MAX_LEN];
    anim_t *next;
    
    int len, fps;
    SDL_Surface **frames;
};

anim_t *anim_create(const wchar_t *name, int len, int fps);
void anim_delete(anim_t *anim);
void anim_add_frame(anim_t *anim, fset_t *frameset, int frame_index);
void anim_set_frames(anim_t *anim, fset_t *frameset, int start_index);
void anim_draw(anim_t *anim, int step, SDL_Surface *target, SDL_Rect *dest);

void anim_list_add(anim_t *head, anim_t *anim);
anim_t *anim_list_get(anim_t *head, const wchar_t *name);
void anim_list_delete(anim_t *head);


#endif
