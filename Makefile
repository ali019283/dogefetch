CC=cc
SOURCES=doge.c
CFLAGS=-O2
EXECUTABLE=dogefetch
PREFIX=/usr/local

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install: all
	mkdir -p /usr/local/share/dogefetch $(PREFIX)/bin/
	cp doggo /usr/local/share/dogefetch/doggo
	cp $(EXECUTABLE) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(EXECUTABLE)
	rm -r /usr/local/share/dogefetch
run: all
	./$(EXECUTABLE)

clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)
