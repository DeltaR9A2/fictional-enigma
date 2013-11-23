#ifndef body_h
#define body_h

#include "rect.h"

typedef struct body_t body_t;
struct body_t{
    rect_t *rect;
    double vx, vy;
};

body_t *body_create(void);
void body_delete(body_t *body);

#endif
