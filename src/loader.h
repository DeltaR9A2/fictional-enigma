#ifndef loader_h
#define loader_h

#include "rect.h"
#include "game.h"

#include "rect_list.h"
#include "fset_wmap.h"
#include "anim_wmap.h"

void load_terrain_rects(game_t *game);
void load_platform_rects(game_t *game);

typedef struct fset_def_t fset_def_t;
struct fset_def_t{
    wchar_t *name;
    char *filename;
    int cols;
    int rows;
    bool flip;
};

void load_framesets(game_t *game);

typedef struct anim_def_t anim_def_t;
struct anim_def_t{
    wchar_t *fset;
    wchar_t *name;
    int start;
    int len;
    int fps;
};

void load_animations(game_t *game);

#endif
