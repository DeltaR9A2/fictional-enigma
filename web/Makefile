
PAGES := index about credits
PAGE_SOURCES := $(PAGES:%=./%.txt)
PAGE_OUTPUTS := $(PAGES:%=./%.html)
PAGE_TEMPLATE := template.html

EXTRA_FILES := styles.css

RSYNC := rsync -e ssh -av $(PAGE_OUTPUTS) $(EXTRA_FILES) dreamerone@ninmunanmu.com:~/ninmunanmu.com/

REMOVE := rm -f

all: $(PAGE_OUTPUTS)

%.html: %.txt
	sed -e "/CONTENT/r $<" -e "/CONTENT/d" $(PAGE_TEMPLATE) > $@

upload:
	$(RSYNC)

clean:
	$(REMOVE) $(PAGE_OUTPUTS)


