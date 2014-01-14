#include <stdlib.h>

#include "target.h"

const uint8_t TARGET_NONE = 0;
const uint8_t TARGET_INFO = 1;
const uint8_t TARGET_TEST = 2;

target_t *target_create(void){
    target_t *target = malloc(sizeof(target_t));

    target->type = TARGET_NONE;
    target->rect = rect_create();
    target->color = 0x00000000;
    target->action = &target_activate;
    return target;
}

void target_delete(target_t *target){
    rect_delete(target->rect);
    free(target);
}

void target_activate(target_t *target, game_t *game){
    printf("Target Activate %08X\n", target->color);
}

