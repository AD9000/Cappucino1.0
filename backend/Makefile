BOARDDIR=boards

CC=g++

all: rfind bfind engine

.PHONY: findRookMagics
rfind: findRookMagics.cpp
	$(CC) -o rfind findRookMagics.cpp

.PHONY: findBishopMagics
bfind: findBishopMagics.cpp
	$(CC) -o bfind findBishopMagics.cpp


.PHONY: engine
engine:	engine.o $(BOARDDIR)/board.o

engine.o: engine.cpp 
	g++ -c engine.cpp

$(BOARDDIR)/board.o: $(BOARDDIR)/board.hpp $(BOARDDIR)/bitboard.hpp $(BOARDDIR)/bitboard.cpp
	+$(MAKE) -C boards


.PHONY: clean
clean:
	rm $(BOARDDIR)/board.o
	rm engine.o
