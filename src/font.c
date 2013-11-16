#include "font.h"

const wchar_t *glyph_order = L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

font_t *font_create(const char *image_fn){
    font_t *font = malloc(sizeof(font_t));
    memset(font, 0, sizeof(font_t));

    font->src = load_image(image_fn);
    
    uint32_t *pixels = font->src->pixels;

    uint32_t this_mark = 0;
    uint32_t prev_mark = 0;
    uint32_t mark_color = pixels[0];

    uint32_t glyph_index = 0;
    uint32_t glyph_count = wcslen(glyph_order);
    
    /* for(int i=0; i<MAX_GLYPHS; i++){
        font->glyphs[i].x = 0;
        font->glyphs[i].y = 0;
        font->glyphs[i].w = 0;
        font->glyphs[i].h = 0;
    } */
    
    while(glyph_index < glyph_count){
        while(pixels[this_mark] == mark_color){
            if(this_mark > font->src->w){ break; }
            this_mark += 1;
        }
        
        prev_mark = this_mark;
        
        while(pixels[this_mark] != mark_color){
            if(this_mark > font->src->w){ break; }
            this_mark += 1;
        }
        
        if(this_mark > font->src->w){
            fprintf(stderr, "Warning: font_init: Font source shorter than glyph list.\n");
            break;
        }
        
        font->glyphs[glyph_order[glyph_index]].x = prev_mark;
        font->glyphs[glyph_order[glyph_index]].w = this_mark - prev_mark;
        font->glyphs[glyph_order[glyph_index]].y = 0;
        font->glyphs[glyph_order[glyph_index]].h = font->src->h;
        glyph_index += 1;
    }
    
    return font;
}

void font_delete(font_t *font){
    SDL_FreeSurface(font->src);
    free(font);
}

void font_draw_all_glyphs(font_t *font, int x, int y, SDL_Surface *target){
    SDL_Rect target_rect;
    target_rect.x = x;
    target_rect.y = y;
    for(int i=0; i<MAX_GLYPHS; i++){
        SDL_BlitSurface(font->src, &(font->glyphs[i]), target, &target_rect);
        target_rect.x += font->glyphs[i].w;
    }
}

void font_draw_string(font_t *font, wchar_t *string, int32_t x, int32_t y, SDL_Surface *target){
    SDL_Rect target_rect;
    target_rect.x = x;
    target_rect.y = y;
    for(int i=0; i<wcslen(string); i++){
        SDL_BlitSurface(font->src, &(font->glyphs[string[i]]), target, &target_rect);
        target_rect.x += font->glyphs[string[i]].w;
    }
}

