#include "animation.h"

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

anim_t *anim_create(int len, int fps){
    anim_t *anim = malloc(sizeof(anim_t));
    anim->len = len;
    anim->fps = fps;
    anim->frames = malloc(sizeof(SDL_Surface*)*(anim->len));
    for(int i=0; i < anim->len; i++){
        anim->frames[i] = NULL;
    }
    return anim;
}

void anim_delete(anim_t *anim){
    free(anim->frames);
    free(anim);
}

void anim_add_frame(anim_t *anim, frameset_t *frameset, int frame_index){
    for(int i=0; i < anim->len; i++){
        if(anim->frames[i] == NULL){
            anim->frames[i] = frameset->frames[frame_index];
            return;
        }
    }
    fprintf(stderr,"Warning: anim_add_frame: No more room for frame");
}

void anim_set_frames(anim_t *anim, frameset_t *frameset, int start_index){
    for(int i=0; i < anim->len; i++){
        anim->frames[i] = frameset->frames[start_index + i];
    }
}    

void anim_draw(anim_t *anim, int step, SDL_Surface *target, SDL_Rect *dest){
    // Magic number 0.01666 is the inverse of 60
    // and 60 is the refresh rate of the main loop
    SDL_BlitSurface(anim->frames[((int)((step*0.01666) * anim->fps)) % anim->len], NULL, target, dest);
}

