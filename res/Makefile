
SRC_IMAGES := $(wildcard ./*.xcf)
OUT_IMAGES := $(SRC_IMAGES:./%.xcf=../bin/%.png)

SRC_SOUNDS := $(wildcard ./*.wav)
OUT_SOUNDS := $(SRC_SOUNDS:./%.wav=../bin/%.ogg)

SRC_FONTS := $(wildcard ./*.ttf)
OUT_FONTS := $(SRC_FONTS:./%.ttf=../bin/%.png)

REMOVE = rm -f

.phony: all images sounds fonts clean clean_images clean_sounds clean_fonts

.SUFFIXES: .xcf .png .wav .ogg .ttf

all: images sounds fonts

images: $(OUT_IMAGES)

../bin/%.png: ./%.xcf
	convert $< -background none -flatten $@

sounds: $(OUT_SOUNDS)

../bin/%.ogg: ./%.wav
	ffmpeg -i $< -codec:a libvorbis $@

fonts: $(OUT_FONTS)

../bin/%.png: ./%.ttf
	./make_font.py --out $@ --size 16 $<

clean_images:
	$(REMOVE) $(OUT_IMAGES)

clean_sounds:
	$(REMOVE) $(OUT_SOUNDS)

clean_fonts:
	$(REMOVE) $(OUT_FONTS)

clean: clean_images clean_sounds clean_fonts

