#include "sdl_helpers.h"

image_dict_t *image_cache = NULL;
image_dict_t *flipped_cache = NULL;

SDL_Surface *create_surface(int32_t w, int32_t h){
	return SDL_CreateRGBSurface(0,w,h,32,0xFF000000,0x00FF0000,0x0000FF00,0x000000FF);
}

SDL_Surface *convert_surface(SDL_Surface *src){
	return SDL_ConvertSurfaceFormat(src, SDL_PIXELFORMAT_RGBA8888, 0);
}

SDL_Surface *load_image(const char *fn){
	image_t *im;
	SDL_Surface *tmp, *final;
	
	if(image_cache == NULL){
		image_cache = image_dict_create();
	}
	
	im = image_dict_get(image_cache, fn);
	
	if(im->surface == NULL){
		tmp = IMG_Load(fn);
	
		if(tmp == NULL){
			printf("LOAD IMAGE FAILED %s\n", fn);
			printf("This will probably crash the game...\n");	 
			return NULL;
		}
	
		final = convert_surface(tmp);
		SDL_FreeSurface(tmp);

		im->surface = final;
	}

	return im->surface;
}

SDL_Surface *flip_surface(SDL_Surface *src){
	return zoomSurface(src, -1, 1, SMOOTHING_OFF);
}

SDL_Surface *load_image_flipped(const char *fn){
	image_t *im;
	SDL_Surface *tmp, *final;

	if(flipped_cache == NULL){
		flipped_cache = image_dict_create();
	}
	
	im = image_dict_get(flipped_cache, fn);
	
	if(im->surface == NULL){
		tmp = load_image(fn);
		final = flip_surface(tmp);
		im->surface = final;
	}
	
	return im->surface;
}

void clear_image_cache(void){
	if(image_cache != NULL){ image_dict_delete(image_cache); }
	if(flipped_cache != NULL){ image_dict_delete(flipped_cache); }
}

SDL_Texture *create_texture(SDL_Renderer *render, int32_t w, int32_t h){
	return SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w, h);
}

SDL_Texture *create_streaming_texture(SDL_Renderer *render, int32_t w, int32_t h){
	return SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}

bool sdl_rect_overlap(SDL_Rect *a, SDL_Rect *b){
		if((a->x + a->w) <= (b->x) || (a->x) >= (b->x + b->w) ||
		   (a->y + a->h) <= (b->y) || (a->y) >= (b->y + b->h)){
			return false;
		}else{
			return true;
		}
}

