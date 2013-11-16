#include "game.h"

frameset_t *frameset_test;
anim_t *anim_test;
SDL_Rect anim_test_rect;

void game_init(game_t *game, core_t *core){
    game->core = core;
    game->step = 0;
    game->font = font_create("font_8bit_operator_black.png");
    
    frameset_test = frameset_create("player_blue_robot.png", 8, 4);
    anim_test = anim_create(6, 10);
    anim_set_frames(anim_test, frameset_test, 1);
    anim_test_rect.x = 100;
    anim_test_rect.y = 100;
}

void game_quit(game_t *game){
    anim_delete(anim_test);    
    frameset_delete(frameset_test);
    font_delete(game->font);
}

void game_fast_frame(game_t *game){
    game->step += 1;
    
    if(controller_pressed(&game->core->controller, BTN_L|BTN_R)){
            
    }else if(controller_pressed(&game->core->controller, BTN_L)){
        anim_test_rect.x -= 1;
    }else if(controller_pressed(&game->core->controller, BTN_R)){
        anim_test_rect.x += 1;
    }
}

void game_full_frame(game_t *game){
    game_fast_frame(game);
    SDL_FillRect(game->core->screen, NULL, 0xFFFFFFFF);
    font_draw_string(game->font, L"I am not a robot.", 0, 0, game->core->screen);
    anim_draw(anim_test, game->step, game->core->screen, &anim_test_rect);
}

