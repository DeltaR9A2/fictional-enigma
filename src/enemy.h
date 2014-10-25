#ifndef enemy_h
#define enemy_h

typedef struct enemy_t enemy_t;

#include "rect.h"
#include "body.h"
#include "game.h"

struct enemy_t{
	rect_t *rect;
	rect_t *weapon;
	
	body_t *body;
	
	int32_t flashing;

	int32_t durability;
	int32_t damage;

	uint8_t alive;
};

enemy_t *enemy_create(void);
void enemy_init(enemy_t *enemy, double x, double y, double w, double h);
void enemy_delete(enemy_t *enemy);

void enemy_update(enemy_t *enemy, game_t *game);

#endif
