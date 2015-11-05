CC = clang++
CFLAGS = -Wall -std=c++11

BIN = battleship
.PHONY: all

OBJ = \
	types.o \
	ship.o \
	ui.o \
	util.o \
	map.o \
	gm.o \
	main.o

DOBJ = $(wildcard bld/*.o)

all: test

final: $(OBJ)
	$(CC) -O2 -o $(BIN) $(DOBJ) $(LIBS)

%.o: src/%.cpp
	$(CC) -c -o bld/$@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(DOBJ) $(LIBS)

debug:
	$(CC) $(CFLAGS) -g -o $(BIN) $(DOBJ) $(LIBS)

clean:
	rm -f *.obj
	rm -f $(BIN)

