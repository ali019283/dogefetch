SOURCES=doge.c
EXECUTABLE=dogefetch
PREFIX=/usr/local
CFLAGS += -O2

all:
	$(CC) $(SOURCES) $(CFLAGS) -DINSTALL_PREFIX=\"$(PREFIX)\" -o $(EXECUTABLE)

install: all
	install -D doggo $(DESTDIR)$(PREFIX)/share/dogefetch/doggo
	install -D $(EXECUTABLE) $(DESTDIR)$(PREFIX)/bin/dogefetch
