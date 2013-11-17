#include "core.h"

void core_init(core_t *core){
    core->running = true;
    core->fullscreen = false;

    core->win_vw = 640;
    core->win_vh = 360;
    core->win_cw = 1280;
    core->win_ch = 720;
    
    core->active_rect.x = 0;
    core->active_rect.y = 0;
    core->active_rect.w = 1280;
    core->active_rect.h = 720;

    core->window = SDL_CreateWindow(
        "I am not a robot.",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        core->win_cw,
        core->win_ch,
        SDL_WINDOW_RESIZABLE
    );
    
    if(core->window == NULL){
        printf("Could not create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    core->rend = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_ACCELERATED);
    
    core->screen = create_surface(core->win_vw, core->win_vh);
    core->screen_texture = create_streaming_texture(core->rend, core->win_vw, core->win_vh);

    controller_reset(&core->controller);
}

void core_quit(core_t *core){
    SDL_DestroyTexture(core->screen_texture);
    SDL_FreeSurface(core->screen);
    SDL_DestroyRenderer(core->rend);
    SDL_DestroyWindow(core->window);
}

void core_window_resize(core_t *core, int32_t w, int32_t h){
    core->win_cw = w;
    core->win_ch = h;
    
    double h_scale = (double)core->win_cw / (double)core->win_vw;
    double v_scale = (double)core->win_ch / (double)core->win_vh;
    double scale = (h_scale < v_scale) ? h_scale : v_scale;
    
    core->active_rect.w = scale * core->win_vw;
    core->active_rect.h = scale * core->win_vh;
    core->active_rect.x = (core->win_cw - core->active_rect.w)/2;
    core->active_rect.y = (core->win_ch - core->active_rect.h)/2;
    
    SDL_SetWindowSize(core->window, core->win_cw, core->win_ch);
}

void core_toggle_fullscreen(core_t *core){
    core->fullscreen = !(core->fullscreen);
    
    if(core->fullscreen){
        SDL_SetWindowFullscreen(core->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }else{
        SDL_SetWindowFullscreen(core->window, false);
    }
}

void core_window_redraw(core_t *core){
    SDL_UpdateTexture(core->screen_texture, NULL, core->screen->pixels, core->screen->pitch);
    SDL_RenderClear(core->rend);
    SDL_RenderCopy(core->rend, core->screen_texture, NULL, &core->active_rect);
    SDL_RenderPresent(core->rend);
}

