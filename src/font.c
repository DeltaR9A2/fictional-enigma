#include "font.h"

const wchar_t *glyph_order = L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

font_t *font_create(const char *image_fn){
    font_t *font = malloc(sizeof(font_t));
    memset(font, 0, sizeof(font_t));

    SDL_Surface *font_img = load_image(image_fn);
    
    uint32_t *pixels = font_img->pixels;

    uint32_t this_mark = 0;
    uint32_t prev_mark = 0;
    uint32_t mark_color = pixels[0];

    uint32_t glyph_index = 0;
    SDL_Rect glyph_rect;
    SDL_Surface *glyph_surface;

    uint32_t glyph_count = wcslen(glyph_order);
    
    while(glyph_index < glyph_count){
        while(pixels[this_mark] == mark_color){
            if(this_mark > font_img->w){ break; }
            this_mark += 1;
        }
        
        prev_mark = this_mark;
        
        while(pixels[this_mark] != mark_color){
            if(this_mark > font_img->w){ break; }
            this_mark += 1;
        }
        
        if(this_mark > font_img->w){
            fprintf(stderr, "Warning: font_init: Font source shorter than glyph list.\n");
            break;
        }
        
        glyph_rect.x = prev_mark;
        glyph_rect.w = this_mark - prev_mark;
        glyph_rect.y = 0;
        glyph_rect.h = font_img->h;

        glyph_surface = create_surface(glyph_rect.w, glyph_rect.h);
        SDL_BlitSurface(font_img, &glyph_rect, glyph_surface, NULL);
        
        font->glyphs[glyph_order[glyph_index]] = glyph_surface;

        glyph_index += 1;
    }
    
    SDL_FreeSurface(font_img);
    
    return font;
}

void font_delete(font_t *font){
    for(int i=0; i<MAX_GLYPHS; i++){
        if(font->glyphs[i] != NULL){
            SDL_FreeSurface(font->glyphs[i]);
        }
    }
    
    free(font);
}

void font_draw_all_glyphs(font_t *font, int x, int y, SDL_Surface *target){
    font_draw_string(font, glyph_order, x, y, target);
}

void font_draw_string(font_t *font, const wchar_t *string, int32_t x, int32_t y, SDL_Surface *target){
    SDL_Rect target_rect;
    target_rect.x = x;
    target_rect.y = y;
    for(int i=0; i<wcslen(string); i++){
        SDL_BlitSurface(font->glyphs[string[i]], NULL, target, &target_rect);
        target_rect.x += font->glyphs[string[i]]->w;
    }
}

