#ifndef loader_h
#define loader_h

typedef struct fset_def_t fset_def_t;
typedef struct anim_def_t anim_def_t;

#include "game.h"
#include "cmap.h"


#include "rect_list.h"
#include "fset_dict.h"
#include "anim_dict.h"
#include "target_list.h"

struct fset_def_t{
    wchar_t *name;
    char *filename;
    int cols;
    int rows;
    bool flip;
};

void load_framesets(game_t *game);

struct anim_def_t{
    wchar_t *fset;
    wchar_t *name;
    int start;
    int len;
    int fps;
};

void load_animations(game_t *game);

void load_terrain_rects(game_t *game);
void load_platform_rects(game_t *game);

void load_targets(game_t *game);

#endif
