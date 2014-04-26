#include "battle.h"

/*
void game_update_enemies(game_t *game){
	enemy_node_t *iter;
	for(iter = game->enemies->head; iter; iter = iter->next){
		enemy_update(iter->data, game);
	}
}

void game_check_enemies(game_t *game){
	enemy_node_t *iter;
	for(iter = game->enemies->head; iter; iter = iter->next){
		if(iter->data->flashing > 0){
			iter->data->flashing -= 1;
		}else{
			if(rect_overlap(iter->data->rect, game->player->weapon)){
				iter->data->flashing = 15;
				printf("Enemy hit by player.\n");
			}
		}

		if(game->player->flashing == 0){
			if(rect_overlap(iter->data->weapon, game->player->body->rect)){
				game->player->flashing = 60;
				printf("Player hit by enemy.\n");
			}
		}
	}
}
*/
