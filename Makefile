SOURCES=doge.c
EXECUTABLE=dogefetch
PREFIX=/usr

CFLAGS += -O2

all:
	$(CC) $(SOURCES) $(CFLAGS) -DINSTALL_PREFIX=\"$(PREFIX)\" -o $(EXECUTABLE)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/share/dogefetch $(DESTDIR)$(PREFIX)/bin
	cp doggo $(DESTDIR)$(PREFIX)/share/dogefetch/doggo
	cp $(EXECUTABLE) $(DESTDIR)$(PREFIX)/bin
