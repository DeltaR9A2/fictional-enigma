#include "frameset.h"

frameset_t *frameset_create(const char *fn, int cols, int rows){
    SDL_Surface *tmp = load_image(fn);
    SDL_Rect frame_rect;
    frame_rect.x = 0;
    frame_rect.y = 0;
    frame_rect.w = tmp->w / cols;
    frame_rect.h = tmp->h / rows;
    
    SDL_Surface *frame = NULL;
    frameset_t *frameset = malloc(sizeof(frameset_t));
    
    frameset->len = cols * rows;
    frameset->frames = malloc(sizeof(SDL_Surface*)*(frameset->len));
    
    for(int r=0; r<rows; r++){
        for(int c=0; c<cols; c++){ // lol c++ >_>
            frame = create_surface(frame_rect.w, frame_rect.h);
            frame_rect.x = c * frame_rect.w;
            frame_rect.y = r * frame_rect.h;
            SDL_BlitSurface(tmp, &frame_rect, frame, NULL);
            frameset->frames[c+(r*cols)] = frame;
        }
    }
    
    SDL_FreeSurface(tmp);
    
    return frameset;
}

void frameset_delete(frameset_t *frameset){
    for(int i=0; i<frameset->len; i++){
        SDL_FreeSurface(frameset->frames[i]);
    }
    free(frameset->frames);
    free(frameset);
}

