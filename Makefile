CC=gcc
SOURCES=doge.c
CFLAGS=-O2
EXECUTABLE=dogefetch
PREFIX=/usr/local/bin

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	mkdir /usr/share/dogefetch
	cp doggo /usr/share/dogefetch/doggo
	cp $(EXECUTABLE) $(PREFIX)/

uninstall:
	rm -f $(PREFIX)/$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)
