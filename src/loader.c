#include "loader.h"

rect_t static_terrain[] = {
    {    0,     0, 40*16,    16},
    {    0, 21*16, 40*16,    16},
    {    0,     0,    16, 22*16},    
    {39*16,     0,    16, 22*16},
    {    0,     0,     0,     0},
};

rect_t static_platforms[] = {
    { 16,  9*16, 5*16,  16},
    { 16, 13*16, 5*16,  16},
    { 16, 17*16, 5*16,  16},
    {  0,   0,   0,   0},
};

fset_def_t static_framesets[] = {
    {L"p_frost_f_r", "player_frost_female.png",  8,  8, false},
    {L"p_frost_f_l", "player_frost_female.png",  8,  8, true },
    {NULL, NULL, 0, 0},
};

anim_def_t static_animations[] = {
    {L"p_frost_f_r", L"frost_f_idle_r",  0,  4,  5},
    {L"p_frost_f_r", L"frost_f_move_r",  8,  8, 10},
    {L"p_frost_f_r", L"frost_f_jump_r", 16,  2,  8},
    {L"p_frost_f_r", L"frost_f_hang_r", 18,  2,  8},
    {L"p_frost_f_r", L"frost_f_fall_r", 20,  2,  8},
    {L"p_frost_f_r", L"frost_f_skid_r", 22,  2,  8},
    {L"p_frost_f_l", L"frost_f_idle_l",  0,  4,  5},
    {L"p_frost_f_l", L"frost_f_move_l",  8,  8, 10},
    {L"p_frost_f_l", L"frost_f_jump_l", 16,  2,  8},
    {L"p_frost_f_l", L"frost_f_hang_l", 18,  2,  8},
    {L"p_frost_f_l", L"frost_f_fall_l", 20,  2,  8},
    {L"p_frost_f_l", L"frost_f_skid_l", 22,  2,  8},
    {NULL, NULL, 0, 0, 0},
};

void load_terrain_rects(game_t *game){
    rect_t *terrain;
    for(int i=0; rect_get_area(&static_terrain[i]); i++){
        terrain = rect_list_get(game->terr_rect_list);
        rect_match_to(terrain, &static_terrain[i]);
    }
}

void load_platform_rects(game_t *game){
    rect_t *platform;
    for(int i=0; rect_get_area(&static_platforms[i]); i++){
        platform = rect_list_get(game->plat_rect_list);
        rect_match_to(platform, &static_platforms[i]);
    }
}
   
void load_framesets(game_t *game){
    fset_t *fset;
    fset_def_t *def;
    for(int i=0; static_framesets[i].name != NULL; i++){
        def = &static_framesets[i];
        fset = fset_wmap_get(game->fsets, def->name);
        fset_init(fset, def->filename, def->cols, def->rows, def->flip);
    }
}

void load_animations(game_t *game){
    fset_t *fset;
    anim_t *anim;
    anim_def_t *def;
    for(int i=0; static_animations[i].name != NULL; i++){
        def = &static_animations[i];
        fset = fset_wmap_get(game->fsets, def->fset);
        anim = anim_wmap_get(game->anims, def->name);
        anim_init(anim, fset, def->start, def->len, def->fps);
    }
}

