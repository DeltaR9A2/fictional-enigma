
# Standard Linux Build ########
export CC := gcc
export PC := pkg-config
export PACKAGES := sdl2 SDL2_image SDL2_gfx SDL2_mixer lua
###############################

# MINGW Build for Windows #####
#export CC := i686-w64-mingw32-gcc
#export PC := i686-w64-mingw32-pkg-config
#export PACKAGES := sdl2 SDL2_image SDL2_mixer SDL2_gfx lua5.1
###############################

# Debug Flags #####
debug : export CFLAGS := -std=c11 -O0 -g `$(PC) --cflags $(PACKAGES)` -I./src -Wall -Werror -D DEBUG
debug : export LFLAGS := -Wl,-rpath,. -g `$(PC) --libs $(PACKAGES)` -lstdc++
debug : all
###################

# Release Flags #####
release : export CFLAGS := -std=c11 -O2 `$(PC) --cflags $(PACKAGES)` -I./src
release : export LFLAGS := -Wl,-rpath,. `$(PC) --libs $(PACKAGES)`
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
