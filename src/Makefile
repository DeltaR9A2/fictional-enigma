
SOURCES := $(wildcard ./*.c)
OBJECTS := $(SOURCES:./%.c=../obj/%.o)
REMOVE := rm -f

all: $(OBJECTS)
	
../obj/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJECTS)

