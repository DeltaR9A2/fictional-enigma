#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "game.h"

static bool main_running = true;

int main_event_watch(void *game, SDL_Event *e){
    if((e->type == SDL_QUIT) || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)){
        main_running = false;
    }else if(e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED){
        core_window_resize(((game_t*)game)->core, e->window.data1, e->window.data2);
    }else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F11){
        core_toggle_fullscreen(((game_t*)game)->core);
    }
    
    return 0;
}

int main(int arc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    core_t core;
    core_init(&core);
    
    game_t game;
    game_init(&game, &core);

    SDL_AddEventWatch(&main_event_watch, &game);
    
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

