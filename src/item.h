#include <stdint.h>

typedef struct item_t item_t;

#include "body.h"
#include "sprite.h"

extern const uint32_t ITEM_ALIVE;
extern const uint32_t ITEM_FALLS;
extern const uint32_t ITEM_SEEKS;

struct item_t{
	uint32_t type;
	body_t *body;
	sprite_t *sprite;
	uint32_t flags;
};

item_t *item_create(void);
void item_delete(item_t *item);


