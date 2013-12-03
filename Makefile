SHELL := /bin/bash

CC      := gcc
DB      := gdb
CFLAGS  := -std=c99 -Wall -O0 -g -I./src -I./gen/out
LFLAGS  := -Wl,-rpath,. -g -lm -lSDL2 -lSDL2_image -lSDL2_gfx

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

.PHONY: all gen clean run debug

all: $(BINDIR)/$(TARGET)

gen:
	$(MAKE) -C gen

$(BINDIR)/$(TARGET): gen $(OBJECTS) $(PNGS)
	@$(CC) ./obj/*.o $(LFLAGS) -o $@
	@echo "Build complete: "$(BINDIR)/$(TARGET)
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<"..."

$(PNGS): $(BINDIR)/%.png : $(RESDIR)/%.xcf
	@convert $< -background none -flatten $@
	@echo "Converted "$<"..."

clean:
	$(MAKE) -C gen clean
	$(REMOVE) $(BINDIR)/* $(OBJECTS) 

run: all
	@echo "Running build: "$(BINDIR)/$(TARGET)
	@(cd $(BINDIR) && exec ./$(TARGET))

debug: all
	@echo "Debugging build: "$(BINDIR)/$(TARGET)
	@(cd $(BINDIR) && exec $(DB) ./$(TARGET))
