#include "game.h"

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;
SDL_Rect arect;

#include "rect.h"
#include "body.h"
#include "cmap.h"

#include "physics.h"
#include "sprite.h"
#include "loader.h"

#include "player.h"

player_t *player;

cmap_t *test_cmap;
int8_t test_cmap_data[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void draw_terrain_rects(game_t *game){
    SDL_Rect fill_rect;

    rect_node_t *iter = game->terr_rect_list->head;
    while(iter != NULL){
        rect_copy_to_sdl(iter->data, &fill_rect);
        SDL_FillRect(game->core->screen, &fill_rect, 0x333366FF);
        iter = iter->next;
    }
}

void draw_platform_rects(game_t *game){
    SDL_Rect fill_rect;

    rect_node_t *iter = game->plat_rect_list->head;
    while(iter != NULL){
        rect_copy_to_sdl(iter->data, &fill_rect);
        SDL_FillRect(game->core->screen, &fill_rect, 0x7777AAFF);
        iter = iter->next;
    }
}

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    game->fonts = font_create("font_8bit_operator_black.png");
    
    game->fsets = fset_wmap_create();
    game->anims = anim_wmap_create();
    game->terr_rect_list = rect_list_create();
    game->plat_rect_list = rect_list_create();

    load_framesets(game);
    load_animations(game);
    //load_terrain_rects(game);
    //load_platform_rects(game);
    
    test_cmap = cmap_create();
    cmap_init(test_cmap, 1, 20, 16, 16);
    cmap_copy_data_from(test_cmap, test_cmap_data);
    cmap_add_to_rect_list(test_cmap, game->terr_rect_list);
    printf("Terrain Rect Count: %i\n", rect_list_length(game->terr_rect_list));
    game->phys_body_list = body_list_create();
    
    player = player_create();
    
    player->body->rect->x = 64;
    player->body->rect->y = 64;
    player->body->rect->w = 28;
    player->body->rect->h = 38;

    sprite_set_anim(player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));

    controller_reset(&game->controller);
    
    return game;
}

void game_delete(game_t *game){
    player_delete(player);
    
    cmap_delete(test_cmap);

    rect_list_delete(game->plat_rect_list);
    rect_list_delete(game->terr_rect_list);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    
    font_delete(game->fonts);
    
    free(game);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    player_update(player, game);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xDDDDDDFF);
    draw_terrain_rects(game);
    draw_platform_rects(game);

    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(player->body->rect));
    font_draw_string(game->fonts, debug_message, 24, 20, game->core->screen);
    
    rect_copy_to_sdl(player->sprite->rect, &arect);
    if(sdl_rect_overlap(&arect, &game->core->active_rect)){
        anim_draw(player->sprite->anim, player->sprite->step, game->core->screen, &arect);
    }
}

