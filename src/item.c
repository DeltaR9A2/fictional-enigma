#include "item.h"

const uint32_t ITEM_ALIVE = 0x00000001;
const uint32_t ITEM_FALLS = 0x00000002;
const uint32_t ITEM_SEEKS = 0x00000004;

item_t *item_create(void){
	item_t *item = malloc(sizeof(item_t));
	
	item->type = 0;
	item->body = body_create();
	item->sprite = sprite_create();
	item->flags = 0;
	
	return item;
}

void item_delete(item_t *item){
	sprite_delete(item->sprite);
	body_delete(item->body);
	
	free(item);
}
