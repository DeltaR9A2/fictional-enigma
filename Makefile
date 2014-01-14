
export CC      := gcc

# Debug Flags #####
export CFLAGS  := -std=c11 -O0 -g -I./src -Wall -Werror -D DEBUG
export LFLAGS  := -Wl,-rpath,. -g -lm -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer
###################

# Release Flags #####
#export CFLAGS  := -std=c11 -O2 -I./src
#export LFLAGS  := -Wl,-rpath,. -lm -lSDL2 -lSDL2_image -lSDL2_gfx
#####################

TARGET := main
REMOVE  := rm -f

.PHONY: all src res clean_src clean_res clean run

all: src res ./bin/$(TARGET)

res:
	$(MAKE) -C res

src:
	$(MAKE) -C src

./bin/$(TARGET):
	$(CC) $(LFLAGS) ./obj/*.o -o $@

run: all
	@(cd bin && exec ./$(TARGET))

clean_src:
	$(MAKE) -C src clean
	$(REMOVE) ./bin/$(TARGET)

clean_res:
	$(MAKE) -C res clean

clean: clean_src clean_res


