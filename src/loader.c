#include "loader.h"
cmap_t *test_cmap;

fset_def_t static_framesets[] = {
    {L"p_frost_f_r", "player_frost_female.png",  8,  8, false},
    {L"p_frost_f_l", "player_frost_female.png",  8,  8, true },
    {NULL, NULL, 0, 0},
};

anim_def_t static_animations[] = {
    {L"p_frost_f_r", L"frost_f_idle_r",  0,  4,  5},
    {L"p_frost_f_r", L"frost_f_duck_r",  4,  4,  5},
    {L"p_frost_f_r", L"frost_f_move_r",  8,  8, 10},
    {L"p_frost_f_r", L"frost_f_jump_r", 16,  2,  8},
    {L"p_frost_f_r", L"frost_f_hang_r", 18,  2,  8},
    {L"p_frost_f_r", L"frost_f_fall_r", 20,  2,  8},
    {L"p_frost_f_r", L"frost_f_skid_r", 22,  2,  8},

    {L"p_frost_f_l", L"frost_f_idle_l",  0,  4,  5},
    {L"p_frost_f_l", L"frost_f_duck_l",  4,  4,  5},
    {L"p_frost_f_l", L"frost_f_move_l",  8,  8, 10},
    {L"p_frost_f_l", L"frost_f_jump_l", 16,  2,  8},
    {L"p_frost_f_l", L"frost_f_hang_l", 18,  2,  8},
    {L"p_frost_f_l", L"frost_f_fall_l", 20,  2,  8},
    {L"p_frost_f_l", L"frost_f_skid_l", 22,  2,  8},
    {NULL, NULL, 0, 0, 0},
};

void load_terrain_rects(game_t *game){
    SDL_Surface *test_map_image = load_image("map_test.png");
    cmap_t *test_cmap = cmap_create();

    cmap_init(test_cmap, 0, 0, 128, 128);
    
    for(int i=0; i < test_map_image->w * test_map_image->h; i++){
        uint32_t pixel = ((Uint32 *)test_map_image->pixels)[i];
        if(pixel == 0x333366FF){
            test_cmap->data[i] = 1;
        }else{
            test_cmap->data[i] = 0;
        }
    }
    
    cmap_add_to_rect_list(test_cmap, game->terrain_rects);
    printf("Terrain Rect Count: %i\n", rect_list_length(game->terrain_rects));

    cmap_delete(test_cmap);
    SDL_FreeSurface(test_map_image);
}

void load_platform_rects(game_t *game){
    SDL_Surface *test_map_image = load_image("map_test.png");
    cmap_t *test_cmap = cmap_create();

    cmap_init(test_cmap, 0, 0, 128, 128);
    
    for(int i=0; i < test_map_image->w * test_map_image->h; i++){
        uint32_t pixel = ((Uint32 *)test_map_image->pixels)[i];
        if(pixel == 0x9999DDFF){
            test_cmap->data[i] = 1;
        }else{
            test_cmap->data[i] = 0;
        }
    }
    
    cmap_add_to_rect_list(test_cmap, game->platform_rects);
    printf("Platform Rect Count: %i\n", rect_list_length(game->platform_rects));

    cmap_delete(test_cmap);
    SDL_FreeSurface(test_map_image);
}
   
void load_framesets(game_t *game){
    fset_t *fset;
    fset_def_t *def;
    for(int i=0; static_framesets[i].name != NULL; i++){
        def = &static_framesets[i];
        fset = fset_dict_get(game->fsets, def->name);
        fset_init(fset, def->filename, def->cols, def->rows, def->flip);
    }
}

void load_animations(game_t *game){
    fset_t *fset;
    anim_t *anim;
    anim_def_t *def;
    for(int i=0; static_animations[i].name != NULL; i++){
        def = &static_animations[i];
        fset = fset_dict_get(game->fsets, def->fset);
        anim = anim_dict_get(game->anims, def->name);
        anim_init(anim, fset, def->start, def->len, def->fps);
    }
}

void load_targets(game_t *game){
    SDL_Surface *test_map_image = load_image("map_targets.png");
    cmap_t *test_cmap = cmap_create();

    for(int i=0; i < test_map_image->w * test_map_image->h; i++){
        uint32_t pixel = ((Uint32 *)test_map_image->pixels)[i];
        if(pixel != 0xFFFFFFFF){
            target_t *target = target_list_get(game->targets);
            target->rect->x = (i % 128) * 8;
            target->rect->y = (i / 128) * 8;
            target->rect->w = 8;
            target->rect->h = 8;
            target->color = pixel;
        }
    }
    
    SDL_FreeSurface(test_map_image);
}

