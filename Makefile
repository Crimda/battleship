CC = clang++
CFLAGS = -Wall

BIN = battleship
.PHONY: all

OBJ = \
	main.o

DOBJ = \
	bld/main.o

all: test

final:
	$(CC) -O2
	@echo "Not yet supported"

%.o: src/%.cpp
	$(CC) -c -o bld/$@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(DOBJ) $(LIBS)

debug:
	$(CC) $(CFLAGS) -g -o $(BIN) $(DOBJ) $(LIBS)

clean:
	rm -f *.obj
	rm -f $(BIN)

