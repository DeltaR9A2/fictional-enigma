#include <tgmath.h>

#include <SDL2/SDL_mixer.h>

typedef struct mixer_t mixer_t;


struct mixer_t{
	int32_t channels;
	Mix_Chunk *test_sound;
};

mixer_t *mixer_create(void);
	
void mixer_delete(mixer_t *mixer);

int decimal_volume(double volume);
