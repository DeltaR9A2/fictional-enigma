
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:./%.c=../obj/%.o)
REMOVE := rm -f

.phony: all obj clean

all:
	$(MAKE) -C gen
	$(MAKE) obj

obj: $(OBJECTS)

../obj/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C gen clean
	$(REMOVE) $(OBJECTS)

