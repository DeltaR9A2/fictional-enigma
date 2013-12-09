
COMMAND = sed s:TYPE:$(TYPE):g <$< >$@

SRCDIR := ../src
OBJDIR := ../obj

LISTS := body rect
LIST_SOURCES := $(LISTS:%=$(SRCDIR)/%_list.c)
LIST_HEADERS := $(LISTS:%=$(SRCDIR)/%_list.h)

WMAPS := fset anim
WMAP_SOURCES := $(WMAPS:%=$(SRCDIR)/%_wmap.c)
WMAP_HEADERS := $(WMAPS:%=$(SRCDIR)/%_wmap.h)

ALL_HEADERS := $(LIST_HEADERS) $(WMAP_HEADERS)
ALL_SOURCES := $(LIST_SOURCES) $(WMAP_SOURCES)

OBJECTS := $(ALL_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o) 

ALL_FILES := $(ALL_HEADERS) $(ALL_SOURCES) $(OBJECTS)

REMOVE  := rm -f

all: $(ALL_FILES)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<"..."

$(LISTS): $(LIST_HEADERS) $(LIST_SOURCES)

$(LIST_HEADERS): list_template.h
	$(eval TYPE := $(@F:%_list.h=%))
	$(COMMAND)

$(LIST_SOURCES): list_template.c
	$(eval TYPE := $(@F:%_list.c=%))
	$(COMMAND)

$(WMAPS): $(WMAP_HEADERS) $(WMAP_SOURCES)

$(WMAP_HEADERS): wmap_template.h
	$(eval TYPE := $(@F:%_wmap.h=%))
	$(COMMAND)

$(WMAP_SOURCES): wmap_template.c
	$(eval TYPE := $(@F:%_wmap.c=%))
	$(COMMAND)

clean:
	$(REMOVE) $(ALL_FILES)

