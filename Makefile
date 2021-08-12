CC=gcc
SOURCES=doge.c
CFLAGS=-O2
EXECUTABLE=dogefetch
PREFIX=/opt

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	mkdir -p $(PREFIX)/dogefetch/dogefetch $(PREFIX)/dogefetch/bin
	cp doggo $(PREFIX)/dogefetch/doggo
	cp $(EXECUTABLE) $(PREFIX)/dogefetch/bin/

uninstall:
	rm -f $(PREFIX)/dogefetch

run: all
	./$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)
