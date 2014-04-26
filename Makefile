
export CC := gcc

# Debug Flags #####
export CFLAGS := -std=c11 -O0 -g -I./src -Wall -Werror -D DEBUG
export LFLAGS := -Wl,-rpath,. -g -lm -llua -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer
###################

# Release Flags #####
#export CFLAGS := -std=c11 -O2 -I./src
#export LFLAGS := -Wl,-rpath,. -lm -llua -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer
#####################

TARGET := main
REMOVE  := rm -f

.PHONY: all src res clean_src clean_res clean run $(TARGET)

all: src res $(TARGET)

res:
	$(MAKE) -C res

src:
	$(MAKE) -C src

$(TARGET):
	$(CC) $(LFLAGS) ./obj/*.o -o ./bin/$@

run: all
	@(cd bin && exec ./$(TARGET))

clean_src:
	$(MAKE) -C src clean
	$(REMOVE) ./bin/$(TARGET)

clean_res:
	$(MAKE) -C res clean

clean: clean_src clean_res
	$(REMOVE) ./bin/*
	$(REMOVE) ./obj/*


