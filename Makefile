
export CC := gcc

# Debug Flags #####
debug : export CFLAGS := -std=c11 -O0 -g `sdl2-config --cflags` -I./src -Wall -Werror -D DEBUG
debug : export LFLAGS := -Wl,-rpath,. -g -lm -llua `sdl2-config --libs` -lSDL2_image -lSDL2_gfx -lSDL2_mixer
debug : all
###################

# Release Flags #####
release : export CFLAGS := -std=c11 -O2 `sdl2-config --cflags` -I./src
release : export LFLAGS := -Wl,-rpath,. -lm -llua `sdl2-config --libs` -lSDL2_image -lSDL2_gfx -lSDL2_mixer
release : all
#####################

TARGET := nnlaf
REMOVE  := rm -f

.PHONY: all src res clean_src clean_res clean run $(TARGET) debug release

all: src res $(TARGET)

res:
	$(MAKE) -C res

src:
	$(MAKE) -C src

$(TARGET):
	$(CC) ./obj/*.o $(LFLAGS) -o ./bin/$@

run:
	@(cd bin && exec ./$(TARGET))

clean_src:
	$(MAKE) -C src clean
	$(REMOVE) ./bin/$(TARGET)

clean_res:
	$(MAKE) -C res clean

clean: clean_src clean_res
	$(REMOVE) ./bin/*
	$(REMOVE) ./obj/*

debug: all

release: all
