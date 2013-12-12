#include "game.h"

wchar_t debug_message[128];
SDL_Surface *debug_message_surface;

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    
    game->controller = controller_create();
    game->mouse = rect_create();
    game->bounds = rect_create();
    game->camera = camera_create();
    game->player = player_create();
    
    game->fsets = fset_wmap_create();
    game->anims = anim_wmap_create();
    game->terr_rect_list = rect_list_create();
    game->plat_rect_list = rect_list_create();
    game->phys_body_list = body_list_create();

    game->font = font_create("font_8bit.png");

    rect_init(game->mouse, 0, 0, 8, 8);
    rect_init(game->bounds, 0, 0, 1024, 1024);
    camera_init(game->camera, 640, 360);

    debug_message_surface = create_surface(640, 3+font_get_height(game->font));

    load_framesets(game);
    load_animations(game);
    load_terrain_rects(game);
    load_platform_rects(game);
    
    //////////////////////////
    game->player->body->rect->x = 64;
    game->player->body->rect->y = 64;
    game->player->body->rect->w = 28;
    game->player->body->rect->h = 38;
    sprite_set_anim(game->player->sprite, anim_wmap_get(game->anims, L"frost_f_idle_r"));
    //////////////////////////
    
    return game;
}

void game_delete(game_t *game){
    font_delete(game->font);
    
    body_list_delete(game->phys_body_list);
    rect_list_delete(game->plat_rect_list);
    rect_list_delete(game->terr_rect_list);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    
    player_delete(game->player);
    camera_delete(game->camera);
    rect_delete(game->bounds);
    rect_delete(game->mouse);
    controller_delete(game->controller);
    
    free(game);
}

void game_fast_frame(game_t *game){
    int32_t mx, my;
    core_get_mouse_pos(game->core, &mx, &my);

    mx += game->camera->view->x;
    my += game->camera->view->y;
    
    mx = (floor(mx/8.0));
    my = (floor(my/8.0));
    
    game->mouse->x = mx*8;
    game->mouse->y = my*8;

    game->step += 1;
    
    player_update(game->player, game);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    
    rect_move_to(game->camera->view, game->player->body->rect);
    camera_draw_game(game->camera, game);
    SDL_BlitSurface(game->camera->buffer, NULL, game->core->screen, NULL);

    swprintf(debug_message, 100, L"Current Step: %i", game->step);
    SDL_FillRect(debug_message_surface, NULL, 0x000000AA);
    font_draw_string(game->font, debug_message, 4, 2, debug_message_surface);
    SDL_BlitSurface(debug_message_surface, NULL, game->core->screen, NULL);
}

