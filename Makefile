SHELL := /bin/bash

export CC      := gcc

# Debug Flags #####
#export CFLAGS  := -std=c99 -O0 -g -pg -I./src -Wall -Werror -D DEBUG
#export LFLAGS  := -Wl,-rpath,. -g -pg -lm -lSDL2 -lSDL2_image -lSDL2_gfx
###################

# Release Flags #####
export CFLAGS  := -std=c99 -O2 -I./src
export LFLAGS  := -Wl,-rpath,. -lm -lSDL2 -lSDL2_image -lSDL2_gfx
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

XCFS := $(wildcard $(RESDIR)/*.xcf)
PNGS := $(XCFS:$(RESDIR)/%.xcf=$(BINDIR)/%.png) 

REMOVE  := rm -f

.PHONY: all gen ttf clean run debug

all: $(BINDIR)/$(TARGET)

gen:
	$(MAKE) -C gen

ttf:
	$(MAKE) -C ttf

$(BINDIR)/$(TARGET): gen ttf $(OBJECTS) $(PNGS)
	@$(CC) $(LFLAGS) ./obj/*.o -o $@ 
	@echo "Build complete: "$(BINDIR)/$(TARGET)
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<"..."

$(PNGS): $(BINDIR)/%.png : $(RESDIR)/%.xcf
	@convert $< -background none -flatten $@
	@echo "Converted "$<"..."

clean:
	$(MAKE) -C gen clean
	$(MAKE) -C ttf clean
	$(REMOVE) $(BINDIR)/* $(OBJECTS) 

run: all
	@echo "Running build: "$(BINDIR)/$(TARGET)
	@(cd $(BINDIR) && exec ./$(TARGET))

