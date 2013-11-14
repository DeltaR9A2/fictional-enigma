SHELL := /bin/bash

CC      := gcc
CFLAGS  := -std=c99 -Wall -O0 -g -I./lib
LFLAGS  := -Wl,-rpath,. -g -lSDL2 -lSDL2_image

BINDIR  := bin
SRCDIR  := src
OBJDIR  := obj
LIBDIR  := lib
RESDIR  := res

TARGET := main
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o) 

XCFS := $(wildcard $(RESDIR)/*.xcf)
PNGS := $(XCFS:$(RESDIR)/%.xcf=$(BINDIR)/%.png) 

REMOVE  := rm -f

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS) $(PNGS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Build complete: "$(BINDIR)/$(TARGET)
	
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<"..."

$(PNGS): $(BINDIR)/%.png : $(RESDIR)/%.xcf
	@convert $< -background none -flatten $@
	@echo "Converted "$<"..."

clean:
	$(REMOVE) $(OBJECTS) $(BINDIR)/*

run: all
	@echo "Running build: "$(BINDIR)/$(TARGET)
	@(cd $(BINDIR) && exec ./$(TARGET))

