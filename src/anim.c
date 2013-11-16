#include "anim.h"

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

