#include "game.h"

fset_t *fset_one = NULL;
anim_t *anim_one = NULL;
anim_t *anim_two = NULL;

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

typedef struct camera_t camera_t;
struct camera_t{
    rect_t *view;
    SDL_Surface *buffer;
};

camera_t *camera_create(void){
    camera_t *camera = malloc(sizeof(camera_t));
    camera->view = rect_create();
    camera->buffer = NULL;
    return camera;
}

void camera_init(camera_t *camera, int32_t w, int32_t h){
    camera->view->w = w;
    camera->view->h = h;
    camera->buffer = create_surface(w, h);
}

void camera_delete(camera_t *camera){
    rect_delete(camera->view);
    SDL_FreeSurface(camera->buffer);
}

void camera_draw_player(camera_t *camera, player_t *player){
    SDL_Rect draw_rect;

    rect_copy_to_sdl(player->sprite->rect, &draw_rect);
    
    draw_rect.x -= camera->view->x;
    draw_rect.y -= camera->view->y;
    
    anim_draw(player->sprite->anim, player->sprite->step, camera->buffer, &draw_rect);
}

void camera_fill_rect(camera_t *camera, rect_t *rect, int32_t color){
    SDL_Rect fill_rect;

    rect_copy_to_sdl(rect, &fill_rect);
    
    fill_rect.x -= camera->view->x;
    fill_rect.y -= camera->view->y;

    SDL_FillRect(camera->buffer, &fill_rect, color);
}

void camera_draw_terrain_rects(camera_t *camera, game_t *game){
    rect_node_t *iter = game->terr_rect_list->head;
    while(iter != NULL){
        camera_fill_rect(camera, iter->data, 0x333366FF);
        iter = iter->next;
    }
}

void camera_draw_platform_rects(camera_t *camera, game_t *game){
    rect_node_t *iter = game->plat_rect_list->head;
    while(iter != NULL){
        camera_fill_rect(camera, iter->data, 0x7777AAFF);
        iter = iter->next;
    }
}

#include <tgmath.h>

void camera_draw_game(camera_t *camera, game_t *game){
    SDL_FillRect(camera->buffer, NULL, 0x000000FF);

    camera_fill_rect(camera, game->bounds, 0xDDDDDDFF);
    
    camera_draw_terrain_rects(camera, game);
    camera_draw_platform_rects(camera, game);
    camera_draw_player(camera, player);
    
//    int32_t mx, my;
//    core_get_mouse_pos(game->core, &mx, &my);
//    mx += camera->view->x;
//    my += camera->view->y;
//    mx = (floor(mx/8.0))*8;
//    my = (floor(my/8.0))*8;
    
//    fill_rect.w = 8;
//    fill_rect.h = 8;
//    fill_rect.x = mx;
//    fill_rect.y = my;
    
//    fill_rect.x -= camera->view->x;
//    fill_rect.y -= camera->view->y;
    
//    SDL_FillRect(camera->buffer, &fill_rect, 0xFF0000FF);
}

camera_t *camera;

wchar_t debug_message[128];

game_t *game_create(core_t *core){
    game_t *game = malloc(sizeof(game_t));
    
    game->core = core;
    game->step = 0;
    
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
    camera = camera_create();
    camera_init(camera, 640, 360);
    //////////////////////////
    
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
    
    camera_delete(camera);
    
    //cmap_delete(test_cmap);

    rect_list_delete(game->plat_rect_list);
    rect_list_delete(game->terr_rect_list);
    anim_wmap_delete(game->anims);
    fset_wmap_delete(game->fsets);
    
    font_delete(game->fonts);
    
    rect_delete(game->bounds);
    
    free(game);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    player_update(player, game);
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    
    rect_move_to(camera->view, player->body->rect);
    
    camera_draw_game(camera, game);
    
    SDL_BlitSurface(camera->buffer, NULL, game->core->screen, NULL);

    swprintf(debug_message, 100, L"Body b_edge: %f", rect_get_b_edge(player->body->rect));
    font_draw_string(game->fonts, debug_message, 24, 20, game->core->screen);   
}

