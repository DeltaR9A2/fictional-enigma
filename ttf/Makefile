

COMMAND = ./make_font.py

SOURCES := $(wildcard ./*.ttf)
OBJECTS := $(SOURCES:./%.ttf=../bin/%.png) 

REMOVE  := rm -f

all: $(OBJECTS)

clean:
	$(REMOVE) $(OBJECTS)    

$(OBJECTS): ../bin/%.png : ./%.ttf
	$(COMMAND) --out $@ $<

