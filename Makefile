CC=gcc
SOURCES=doge.c
CFLAGS=-O2
EXECUTABLE=dogefetch
PREFIX=/usr/local

all:
        $(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
        mkdir -p $(PREFIX)/share/dogefetch $(PREFIX)/bin/
        cp doggo $(PREFIX)/share/dogefetch/doggo
        cp $(EXECUTABLE) $(PREFIX)/bin/

uninstall:
        rm -f $(PREFIX)/bin/$(EXECUTABLE)

run: all
        ./$(EXECUTABLE)

clean: $(EXECUTABLE)
        rm -f $(EXECUTABLE)
