
SRC_IMAGES := $(wildcard ./*.xcf)
OUT_IMAGES := $(SRC_IMAGES:./%.xcf=../bin/$(OS)/%.png)

SRC_SOUNDS := $(wildcard ./*.wav)
OUT_SOUNDS := $(SRC_SOUNDS:./%.wav=../bin/$(OS)/%.ogg)

SRC_MUSIC := $(wildcard ./*.mp3)
OUT_MUSIC := $(SRC_MUSIC:./%.mp3=../bin/$(OS)/%.ogg)

SRC_FONTS := $(wildcard ./*.ttf)
OUT_FONTS := $(SRC_FONTS:./%.ttf=../bin/$(OS)/%.png)

REMOVE = rm -f

.phony: all images sounds music fonts clean clean_images clean_sounds clean_music clean_fonts

.SUFFIXES: .xcf .png .wav .ogg .ttf .mp3

all: images sounds music fonts

images: $(OUT_IMAGES)

../bin/$(OS)/%.png: ./%.xcf
	convert $< -background none -flatten $@

sounds: $(OUT_SOUNDS)

../bin/$(OS)/%.ogg: ./%.wav
	ffmpeg -v 0 -i $< -vn -codec:a libvorbis $@

music: $(OUT_MUSIC)

../bin/$(OS)/%.ogg: ./%.mp3
	ffmpeg -v 0 -i $< -vn -codec:a libvorbis $@

fonts: $(OUT_FONTS)

../bin/$(OS)/%.png: ./%.ttf
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

