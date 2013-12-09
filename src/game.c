#include "game.h"

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    
    game->mouse = rect_create();
    rect_init(game->mouse, 0, 0, 8, 8);
    
    game->bounds = rect_create();
    rect_init(game->bounds, 0, 0, 1000, 1000);
    
    game->fonts = font_create("font_8bit_operator_black.png");
    
    game->fsets = fset_wmap_create();
    game->anims = anim_wmap_create();
    game->terr_rect_list = rect_list_create();
    game->plat_rect_list = rect_list_create();

    load_framesets(game);
    load_animations(game);
    load_terrain_rects(game);
    load_platform_rects(game);
    
    /////////////////////////
    //test_cmap = cmap_create();
    //cmap_init(test_cmap, 1, 20, 16, 16);
    //cmap_copy_data_from(test_cmap, test_cmap_data);
    //cmap_add_to_rect_list(test_cmap, game->terr_rect_list);
    //printf("Terrain Rect Count: %i\n", rect_list_length(game->terr_rect_list));
    //////////////////////////
    
    //////////////////////////
    game->camera = camera_create();
    camera_init(game->camera, 640, 360);
    //////////////////////////
    
    game->phys_body_list = body_list_create();
    
    game->player = player_create();
    
    game->player->body->rect->x = 64;
    game->player->body->rect->y = 64;
    game->player->body->rect->w = 28;
    game->player->body->rect->h = 38;

    sprite_set_anim(game->player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));

    controller_reset(&game->controller);
    
    return game;
}

void game_delete(game_t *game){
    player_delete(game->player);
    
    camera_delete(game->camera);
    
    //cmap_delete(test_cmap);

    rect_list_delete(game->plat_rect_list);
    rect_list_delete(game->terr_rect_list);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    
    font_delete(game->fonts);
    
    rect_delete(game->bounds);
    rect_delete(game->mouse);
    
    free(game);
}

void game_fast_frame(game_t *game){
    int32_t mx, my;
    core_get_mouse_pos(game->core, &mx, &my);

    mx += game->camera->view->x;
    my += game->camera->view->y;
    
    mx = (floor(mx/8.0))*8;
    my = (floor(my/8.0))*8;
    
    game->mouse->x = mx;
    game->mouse->y = my;

    game->step += 1;
    
    player_update(game->player, game);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    
    rect_move_to(game->camera->view, game->player->body->rect);
    
    camera_draw_game(game->camera, game);
    
    SDL_BlitSurface(game->camera->buffer, NULL, game->core->screen, NULL);

    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(game->player->body->rect));
    font_draw_string(game->fonts, debug_message, 24, 20, game->core->screen);   
}

