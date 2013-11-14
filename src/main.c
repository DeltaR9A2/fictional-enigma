#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "game.h"

int main_event_watch(void *core, SDL_Event *e){
    if((e->type == SDL_QUIT) || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)){
        ((core_t *)core)->running = false;
    }
    
    return 0;
}

int main(int arc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    
    core_t core;
    core_init(&core);
    
    SDL_AddEventWatch(&main_event_watch, &core);
    
    game_t game;
    game_init(&game, &core);
    
    int32_t ms_per_frame = 16;
    int32_t curr_ms = SDL_GetTicks();
    int32_t prev_ms = curr_ms;
    int32_t ms_delta = 0;
    int32_t ms_accum = 0;
    
    while(core.running){
        prev_ms = curr_ms;
        curr_ms = SDL_GetTicks();
        ms_delta = curr_ms - prev_ms;
        ms_accum += ms_delta;
        
        if(ms_accum > ms_per_frame){
            ms_accum -= ms_per_frame;

            controller_poll_events(&core.controller);
            
            if(ms_accum > ms_per_frame){
                game_fast_frame(&game);
            }else{
                game_full_frame(&game);
                core_window_redraw(&core);
            }
        }
    }
    
    SDL_Quit();
    
    return 0;
}

