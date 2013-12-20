#include "enemy.h"

enemy_t *enemy_create(void){
    enemy_t *enemy = malloc(sizeof(enemy_t));
    enemy->rect = rect_create();
    enemy->weapon = enemy->rect;
    
    enemy->flashing = 0;
    
    return enemy;
}

void enemy_init(enemy_t *enemy, double x, double y, double w, double h){
    rect_init(enemy->rect, x, y, w, h);
}

void enemy_delete(enemy_t *enemy){
    rect_delete(enemy->rect);
//    rect_delete(enemy->weapon);
    free(enemy);
}
