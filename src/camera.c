#include "camera.h"

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

void camera_fill_rect(camera_t *camera, rect_t *rect, int32_t color){
    SDL_Rect fill_rect;

    rect_copy_to_sdl(rect, &fill_rect);
    
    fill_rect.x -= camera->view->x;
    fill_rect.y -= camera->view->y;

    SDL_FillRect(camera->buffer, &fill_rect, color);
}

void camera_draw_game(camera_t *camera, game_t *game){
    SDL_FillRect(camera->buffer, NULL, 0x000000FF);

    rect_limit_to(camera->view, game->bounds);

    camera_fill_rect(camera, game->bounds, 0xDDDDDDFF);
    
    camera_draw_terrain_rects(camera, game);
    camera_draw_platform_rects(camera, game);
    camera_draw_player(camera, game->player);
    
    camera_fill_rect(camera, game->mouse, 0xFF0000FF);
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

void camera_draw_player(camera_t *camera, player_t *player){
    SDL_Rect draw_rect;

    rect_copy_to_sdl(player->sprite->rect, &draw_rect);
    
    draw_rect.x -= camera->view->x;
    draw_rect.y -= camera->view->y;
    
    anim_draw(player->sprite->anim, player->sprite->step, camera->buffer, &draw_rect);
}

