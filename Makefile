
all: linux win32

debug: linux_debug win32_debug

clean: linux_clean win32_clean

linux:
	$(MAKE) -f Makefile.linux

win32:
	$(MAKE) -f Makefile.win32

linux_debug:
	$(MAKE) -f Makefile.linux debug

win32_debug:
	$(MAKE) -f Makefile.win32 debug

linux_clean:
	$(MAKE) -f Makefile.linux clean

win32_clean:
	$(MAKE) -f Makefile.win32 clean


