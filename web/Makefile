
PAGE_NAMES := index about credits contact
PAGE_SOURCES := $(PAGE_NAMES:%=./src/%.htmf)
PAGE_OUTPUTS := $(PAGE_NAMES:%=./out/%.html)
PAGE_TEMPLATE := ./src/template.html

IMAGE_SOURCES := $(wildcard ./src/img/*.png)
IMAGE_OUTPUTS := $(IMAGE_SOURCES:./src/img/%.png=./out/img/%.png)

EXTRA_FILES := out/styles.css

RSYNC := rsync -e ssh -av ./out/* dreamerone@ninmunanmu.com:~/ninmunanmu.com/

REMOVE := rm -f

all: $(PAGE_OUTPUTS) $(IMAGE_OUTPUTS) $(EXTRA_FILES)

out/%.html: src/%.htmf
	sed -e "/CONTENT/r $<" -e "/CONTENT/d" $(PAGE_TEMPLATE) > $@

out/img/%.png: src/img/%.png
	cp $< $@

out/styles.css: src/styles.sass
	sass ./src/styles.sass ./out/styles.css

upload: all
	$(RSYNC)

clean:
	$(REMOVE) $(PAGE_OUTPUTS) $(IMAGE_OUTPUTS) $(EXTRA_FILES)


