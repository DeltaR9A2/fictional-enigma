#ifndef target_h
#define target_h

#include "rect.h"

typedef struct target_t target_t;

struct target_t{
  uint8_t type;
  rect_t *rect;
  void *data;  
};

target_t *target_create(void);
void target_delete(target_t *target);

#endif
