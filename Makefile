CC=gcc
SOURCES=doge.c
CFLAGS=-O2
EXECUTABLE=dogefetch
PREFIX=/usr/local/bin

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) $(PREFIX)/

uninstall:
	rm -f $(PREFIX)/$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)
