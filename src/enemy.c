#include "enemy.h"

enemy_t *enemy_create(void){
    enemy_t *enemy = malloc(sizeof(enemy_t));
    enemy->rect = rect_create();
    enemy->weapon = enemy->rect;

    enemy->body = body_create();

    enemy->flashing = 0;
    
    return enemy;
}

void enemy_init(enemy_t *enemy, double x, double y, double w, double h){
    rect_init(enemy->rect, x, y, w, h);
    
    rect_match_to(enemy->body->rect, enemy->rect);
    enemy->body->vx = -1;
}

void enemy_delete(enemy_t *enemy){
    body_delete(enemy->body);
    rect_delete(enemy->rect);
//    rect_delete(enemy->weapon);
    free(enemy);
}

void enemy_update(enemy_t *enemy, game_t *game){
    if(enemy->body->flags & BLOCKED_R){
        enemy->body->vx = -1;
    }else if(enemy->body->flags & BLOCKED_L){
        enemy->body->vx = 1;
    }
    
    enemy->body->vy = 4;
    enemy->body->flags |= PLAT_DROP;
    
    do_physics_to_it(enemy->body, game->terrain_rects, game->platform_rects);
    rect_move_to(enemy->rect, enemy->body->rect);
}
