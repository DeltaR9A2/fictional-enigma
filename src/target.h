#ifndef target_h
#define target_h

typedef struct target_t target_t;

#include "rect.h"
#include "game.h"
#include "sprite.h"

struct target_t{
  uint8_t type;
  rect_t *rect;
  uint32_t color;
  void (*action)(target_t*, game_t*);

  sprite_t *sprite;
  char message[128];

  SDL_Surface *portrait;
};

target_t *target_create(void);
void target_delete(target_t *target);

void target_activate(target_t *target, game_t *game);

void target_activate_teal(target_t *target, game_t *game);
void target_activate_gold(target_t *target, game_t *game);
void target_activate_magenta(target_t *target, game_t *game);

#endif
