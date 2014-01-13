
export CC      := gcc

# Debug Flags #####
export CFLAGS  := -std=c11 -O0 -g -I./src -Wall -Werror -D DEBUG
export LFLAGS  := -Wl,-rpath,. -g -lm -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer
###################

# Release Flags #####
#export CFLAGS  := -std=c11 -O2 -I./src
#export LFLAGS  := -Wl,-rpath,. -lm -lSDL2 -lSDL2_image -lSDL2_gfx
#####################

BINDIR  := bin
SRCDIR  := src
OBJDIR  := obj
LIBDIR  := lib
RESDIR  := res
GENDIR  := gen

TARGET := main
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o) 

export REMOVE  := rm -f

.PHONY: all src res gen clean run debug rebuild

all: $(BINDIR)/$(TARGET)

gen:
	$(MAKE) -C gen

res:
	$(MAKE) -C res

$(BINDIR)/$(TARGET): gen res $(OBJECTS)
	@$(CC) $(LFLAGS) ./obj/*.o -o $@ 
	@echo "Build complete: "$(BINDIR)/$(TARGET)
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<"..."

run: all
	@echo "Running build: "$(BINDIR)/$(TARGET)
	@(cd $(BINDIR) && exec ./$(TARGET))

src_clean:
	$(MAKE) -C gen clean
	$(REMOVE) $(BINDIR)/$(TARGET) $(OBJECTS)

res_clean:
	$(MAKE) -C res clean

clean: src_clean res_clean

rebuild: src_clean all

