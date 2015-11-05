CC = clang++
CFLAGS = -Wall

BIN = battleship
.PHONY: all

OBJ = \
	map.o \
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

