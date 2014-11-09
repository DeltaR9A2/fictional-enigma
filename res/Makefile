
SRC_IMAGES := $(wildcard ./*.xcf)
OUT_IMAGES := $(SRC_IMAGES:./%.xcf=../bin/%.png)

SRC_SOUNDS := $(wildcard ./*.wav)
OUT_SOUNDS := $(SRC_SOUNDS:./%.wav=../bin/%.ogg)

SRC_MUSIC := $(wildcard ./*.mp3)
OUT_MUSIC := $(SRC_MUSIC:./%.mp3=../bin/%.ogg)

SRC_FONTS := $(wildcard ./*.ttf)
OUT_FONTS := $(SRC_FONTS:./%.ttf=../bin/%.png)

REMOVE = rm -f

.phony: all images sounds music fonts clean clean_images clean_sounds clean_music clean_fonts

.SUFFIXES: .xcf .png .wav .ogg .ttf .mp3

all: images sounds music fonts

images: $(OUT_IMAGES)

../bin/%.png: ./%.xcf
	convert $< -background none -flatten $@

sounds: $(OUT_SOUNDS)

../bin/%.ogg: ./%.wav
	ffmpeg -i $< -codec:a libvorbis $@

music: $(OUT_MUSIC)

../bin/%.ogg: ./%.mp3
	ffmpeg -i $< -codec:a libvorbis $@

fonts: $(OUT_FONTS)

../bin/%.png: ./%.ttf
	./make_font.py --out $@ --size 16 $<

clean_images:
	$(REMOVE) $(OUT_IMAGES)

clean_sounds:
	$(REMOVE) $(OUT_SOUNDS)

clean_music:
	$(REMOVE) $(OUT_MUSIC)

clean_fonts:
	$(REMOVE) $(OUT_FONTS)

clean: clean_images clean_sounds clean_music clean_fonts

