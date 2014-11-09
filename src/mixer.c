#include <stdlib.h>
#include <stdio.h>

#include "mixer.h"

const int32_t MIXER_CHANNEL_SOUND =	-1;
const int32_t MIXER_CHANNEL_MUSIC =	0;
const int32_t MIXER_CHANNEL_VOICE =	1;

mixer_t *mixer_create(void){
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	mixer_t *mixer = malloc(sizeof(mixer_t));
	
	mixer->channels = 16;
  
	Mix_AllocateChannels(mixer->channels);
	Mix_ReserveChannels(2);

	mixer->test_sound = Mix_LoadWAV("jump.ogg");
	mixer->test_music = Mix_LoadWAV("rocket.ogg");

	Mix_PlayChannel(MIXER_CHANNEL_MUSIC, mixer->test_music, -1);
	
	Mix_Volume(MIXER_CHANNEL_MUSIC, decimal_volume(0.3));
	Mix_Volume(MIXER_CHANNEL_VOICE, decimal_volume(0.3));

	for(uint32_t i = 2; i < 16; i++){
		Mix_Volume(i, decimal_volume(0.5));
	}

	return mixer;
}

void mixer_test_sound(mixer_t *mixer){
	int retval = Mix_PlayChannel(MIXER_CHANNEL_SOUND, mixer->test_sound, 0);
	printf("Playing test sound on channel %i\n", retval);
	if (retval == -1){
		printf("SDL_Mixer error: %s\n", Mix_GetError());
	}
	return;
}
	
void mixer_delete(mixer_t *mixer){
	Mix_HaltChannel(-1);
	Mix_FreeChunk(mixer->test_sound);
	free(mixer);
	
	Mix_CloseAudio();
	Mix_Quit();
}

int32_t decimal_volume(double volume){
	return (int32_t)(volume * MIX_MAX_VOLUME);
}
