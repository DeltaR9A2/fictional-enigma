#include <stdlib.h>

#include "mixer.h"

mixer_t *mixer_create(void){
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    mixer_t *mixer = malloc(sizeof(mixer_t));
    
    mixer->channels = 16;
  
    Mix_AllocateChannels(mixer->channels);

    //mixer->test_sound = Mix_LoadWAV("WhiteSands.ogg");
    //Mix_PlayChannel(-1, mixer->test_sound, -1);        
    
    return mixer;
}
    
void mixer_delete(mixer_t *mixer){
    Mix_HaltChannel(-1);
    //Mix_FreeChunk(mixer->test_sound);
    free(mixer);
    
    Mix_CloseAudio();
    Mix_Quit();
}

int decimal_volume(double volume){
    return round(volume * MIX_MAX_VOLUME);
}
