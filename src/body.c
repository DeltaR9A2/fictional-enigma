#include "body.h"

body_t *body_create(void){
    body_t *body = malloc(sizeof(body_t));
    body->rect = rect_create();
    body->vx = 0;
    body->vy = 0;
    return body;
}

void body_delete(body_t *body){
    rect_delete(body->rect);
    free(body);
}

