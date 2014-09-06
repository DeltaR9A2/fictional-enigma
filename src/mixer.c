#include <stdlib.h>

#include "mixer.h"

const uint32_t MIXER_CHANNEL_SOUND =	-1;
const uint32_t MIXER_CHANNEL_MUSIC =	0;
const uint32_t MIXER_CHANNEL_VOICE =	1;

mixer_t *mixer_create(void){
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	mixer_t *mixer = malloc(sizeof(mixer_t));
	
	mixer->channels = 16;
  
	Mix_AllocateChannels(mixer->channels);
	Mix_ReserveChannels(2);

	mixer->test_sound = Mix_LoadWAV("jump.ogg");
	mixer->test_music = Mix_LoadWAV("broken_reality.ogg");

	Mix_PlayChannel(MIXER_CHANNEL_MUSIC, mixer->test_music, -1);
	
	Mix_Volume(MIXER_CHANNEL_MUSIC, decimal_volume(0.1));
	Mix_Volume(MIXER_CHANNEL_VOICE, decimal_volume(0.1));

	for(uint32_t i = 2; i < 16; i++){
		Mix_Volume(i, decimal_volume(0.5));
	}

	return mixer;
}

void mixer_test_sound(mixer_t *mixer){
	Mix_PlayChannel(MIXER_CHANNEL_SOUND, mixer->test_sound, 0);

	return;
}
	
void mixer_delete(mixer_t *mixer){
	Mix_HaltChannel(-1);
	Mix_FreeChunk(mixer->test_sound);
	free(mixer);
	
	Mix_CloseAudio();
	Mix_Quit();
}

int decimal_volume(double volume){
	return round(volume * MIX_MAX_VOLUME);
}
