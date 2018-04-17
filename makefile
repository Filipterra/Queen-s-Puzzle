CC= g++

CFLAGS= -c -std=c++11

all: CFLAGS+= -O3 -Os
all: executable

debug: CFLAGS+= -D_DEBUG -g
debug: executable

executable: Chess.o Queens_puzzle.o
	$(CC)  Chess.o Queens_puzzle.o -o Chess

Chess.o: Chess.cpp Queens_puzzle.hpp
	$(CC) $(CFLAGS) Chess.cpp

Queens_puzzle.o: Queens_puzzle.cpp Queens_puzzle.hpp Chess_pieces.hpp
	$(CC) $(CFLAGS) Queens_puzzle.cpp

clean:
	rm -f *.o Chess
