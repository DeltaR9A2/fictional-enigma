#!/usr/bin/env python2

import argparse

parser = argparse.ArgumentParser(description='Make a bitmap font from a truetype font.')

parser.add_argument('ttf_file', help='The truetype font to use.')

parser.add_argument('--out', dest='out_name', action='store',
                    help='The file to save output to; defaults to a png in the current directory with the same basename as the ttf file.')
parser.add_argument('--size', dest='font_size', action='store', type=int,
                    help='The font size used for the bitmap font. Defaults to 16.')

args = parser.parse_args()

TTF_FILE = args.ttf_file
FONT_SIZE = args.font_size or 16
OUTPUT_NAME = args.out_name

if OUTPUT_NAME is None:
    dot_index = TTF_FILE.rfind('.')
    OUTPUT_NAME = "./" + TTF_FILE[:dot_index] + ".png"

import pygame

pygame.init()

char_order = """ 1234567890-=!@#$%^&*()_+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]\;',./{}|:"<>?"""

font = pygame.font.Font(TTF_FILE,FONT_SIZE)

char_surface_dict = {}
for char in char_order:
    try:
        char_surface = font.render(char,False,(255,255,255,255))
    except pygame.error:
        char_surface = pygame.Surface((1,1))
        char_surface.fill((0,0,0))
    char_surface_dict[char] = char_surface

max_char_w = 0
max_char_h = 0

for surface in char_surface_dict.values():
    max_char_w = max(surface.get_width(), max_char_w)
    max_char_h = max(surface.get_height(), max_char_h)

sep_surface = pygame.Surface((1, max_char_h));
sep_surface.fill((255,0,255,255))

total_w = 0;
for surface in char_surface_dict.values():
    total_w += sep_surface.get_width();
    total_w += surface.get_width();

font_surface = pygame.Surface((total_w, max_char_h), pygame.SRCALPHA)
font_surface.fill((0,0,0,0))


curr_x = 0;
for char_n, char in enumerate(char_order):
    src_surface = char_surface_dict[char]
    font_surface.blit(sep_surface, (curr_x, 0))
    curr_x += sep_surface.get_width();
    font_surface.blit(src_surface, (curr_x, 0))
    curr_x += src_surface.get_width();

pygame.image.save(font_surface, OUTPUT_NAME)

