
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:./%.c=../obj/$(OS)/%.o)

LUA_SOURCES := $(wildcard ./lua/*.lua)
LUA_OUTPUTS := $(LUA_SOURCES:./lua/%.lua=../bin/$(OS)/%.lua)

REMOVE := rm -f

.phony: all obj clean

all:
	$(MAKE) -C gen
	$(MAKE) obj
	$(MAKE) lua

obj: $(OBJECTS)

../obj/$(OS)/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

lua: $(LUA_OUTPUTS)

../bin/$(OS)/%.lua: ./lua/%.lua
	cp $< $@

clean:
	$(MAKE) -C gen clean
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(LUA_OUTPUTS)

