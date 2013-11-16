#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "game.h"

static bool main_running = true;

int main_event_watch(void *data, SDL_Event *e){
    if((e->type == SDL_QUIT) || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)){
        main_running = false;
    }
    
    return 0;
}

int main(int arc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_AddEventWatch(&main_event_watch, NULL);
    
    core_t core;
    core_init(&core);
    
    game_t game;
    game_init(&game, &core);
    
    double ms_per_frame = 16.66;
    double curr_ms = SDL_GetTicks();
    double prev_ms = curr_ms;
    double ms_delta = 0;
    double ms_accum = 0;
    
    while(main_running && core.running){
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

    game_quit(&game);
    core_quit(&core);

    SDL_Quit();
    
    return 0;
}

